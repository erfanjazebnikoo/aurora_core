/* 
 * @File:     UserInterface.cpp
 * @Author:   Sajjad Rahnama
 *            Erfan Jazeb Nikoo
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 22, 2016
 */

#include "UserInterface.h"
#include "UICmdResponse.h"
#include <iostream>
//#include <mavros_msgs/CommandTOL.h>
using namespace au;

UNIQUE_INSTANCE_VARIABLE(UserInterface)

UserInterface::UserInterface()
{
  uiSocket = new QUdpSocket(this);
  world = au::WorldModel::getInstance();
  behaviours = au::Behaviours::getInstance();
}

UserInterface::~UserInterface()
{
  uiSocket->close();
}

void UserInterface::init()
{
  uiSocket->bind(QHostAddress::LocalHost, 9999);
  connect(uiSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void UserInterface::readPendingDatagrams()
{
  //  ROS_INFO("I Heard command");
  Parser parser;
  parser.pWorld = au::WorldModel::getInstance();
  parser.pBehaviours = au::Behaviours::getInstance();
  QByteArray datagram;
  QHostAddress address;
  quint16 port;

  while (uiSocket->hasPendingDatagrams())
  {
    datagram.resize(uiSocket->pendingDatagramSize());
    uiSocket->readDatagram(datagram.data(), datagram.size(), &address, &port);
    parser.parse(datagram);
    if (parser.doWrite)
      uiSocket->writeDatagram(parser.result().toLatin1(), address, port);
  }

}

void UserInterface::Parser::do_mavros_state()
{
  //  ROS_INFO("I Heard do_mavros_state");

  int connected = pWorld->me.isConnected;
  int armed = pWorld->me.isArmed;
  std::string mode = pWorld->me.mode;

  UICmdResponse response(about::VERSION, lastCommand, UICmdResponse::E_OK);
  response.items.append(UICmdResponse::Item(1, "mavros_connected", QString::number(connected)));
  response.items.append(UICmdResponse::Item(1, "mavros_armed", QString::number(armed)));
  response.items.append(UICmdResponse::Item(1, "mavros_guided", QString::fromStdString(mode)));
  response.items.append(UICmdResponse::Item(1, "mavros_mode", QString::fromStdString(mode)));

  resultString = response.toXML();
  doWrite = true;

}

void UserInterface::Parser::do_take_off(const QString &value)
{
  pBehaviours->takeOff(value);
  doWrite = false;
}

void UserInterface::Parser::do_guided_mode()
{
  pBehaviours->guidedMode();
  doWrite = false;
}

void UserInterface::Parser::do_arm()
{
  pBehaviours->arm();
  doWrite = false;
}

void UserInterface::Parser::do_disarm()
{
  pBehaviours->disarm();
  doWrite = false;
}

void UserInterface::Parser::do_fill_wayPoint(const QString &commands)
{
  fromXMLtoWP(commands, pBehaviours->getWayPoints());
  doWrite = false;
}

bool UserInterface::Parser::fromXMLtoWP(const QString &commands, QList<au::WayPoint> &wp)
{
  wp.clear();
  QDomDocument doc;
  doc.setContent(commands);

  QDomNodeList responseNode = doc.elementsByTagName("response");

  if (responseNode.size() != 1)
    return false;

  QDomElement response = responseNode.at(0).toElement();

  if (!response.hasAttribute("ver") || !response.hasAttribute("cmd"))
    return false;

  QDomNodeList itemsNode = doc.elementsByTagName("item");

  GpsCoordination position;

  for (int i = 0; i < itemsNode.size(); i++)
  {
    QDomElement item = itemsNode.at(i).toElement();

    if (item.hasAttribute("name") && item.hasAttribute("alt") && item.hasAttribute("lon") && item.hasAttribute("lat"))
    {
      position.init(item.attribute("lat").toFloat(), item.attribute("lon").toFloat(), item.attribute("alt").toInt());
      wp.append(au::WayPoint(position));
      //      std::cout << item.attribute("lat").toFloat() << std::endl << item.attribute("lon").toFloat() << std::endl
      //        << item.attribute("alt").toInt() << std::endl;
    }
  }

  return true;

}

void UserInterface::Parser::do_start_mission()
{
  pWorld->init();
  //  au::WorldModel::getInstance()->behaviours.gotoWp(au::WorldModel::getInstance()->itr->lat,
  //    au::WorldModel::getInstance()->itr->lon,
  //    au::WorldModel::getInstance()->itr->alt);
  pWorld->setStartMission(true);
}

void UserInterface::Parser::do_land_mode()
{
//    pBehaviours->loiterMode();
//    doWrite = false;
  pWorld->isHeartSeen = true;
}

void UserInterface::Parser::do_rtl_mode()
{
  pBehaviours->rtlMode();
  doWrite = false;
}

void UserInterface::Parser::do_read_takeoff_gps()
{
  pBehaviours->readTakeoffGps();
  UICmdResponse response(about::VERSION, lastCommand, UICmdResponse::E_OK);
  response.items.append(UICmdResponse::Item(1, "takeoff_lat", QString("%1").arg(pBehaviours->getTakeoffGpsLat(),0,'g',13)));
  response.items.append(UICmdResponse::Item(1, "takeoff_lon", QString("%1").arg(pBehaviours->getTakeoffGpsLon(),0,'g',13)));

  resultString = response.toXML();
  std::cout<<resultString.toStdString()<<std::endl;
  doWrite = true;
}