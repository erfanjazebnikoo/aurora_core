/*
 * UserInterface.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: sajjadmuscle
 */

#include "UserInterface.h"
#include "UICmdResponse.h"
#include "WorldModel.h"
#include <iostream>
//#include <mavros_msgs/CommandTOL.h>
using namespace au;

UNIQUE_INSTANCE_VARIABLE(UserInterface)

UserInterface::UserInterface()
{
  uiSocket = new QUdpSocket(this);
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
  ROS_INFO("I Heard command");
  Parser parser;
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
  ROS_INFO("I Heard do_mavros_state");

  int connected = au::WorldModel::getInstance()->share_memory->getConnected();
  int armed = au::WorldModel::getInstance()->share_memory->getArmed();
  std::string mode = au::WorldModel::getInstance()->share_memory->getMode();

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
  au::WorldModel::getInstance()->behaviours.takeOff(value);
  doWrite = false;
}

void UserInterface::Parser::do_guided_mode()
{
  au::WorldModel::getInstance()->behaviours.guidedMode();
  doWrite = false;
}

void UserInterface::Parser::do_arm()
{
  au::WorldModel::getInstance()->behaviours.arm();
  doWrite = false;
}

void UserInterface::Parser::do_fill_wayPoint(const QString &commands)
{
  fromXMLtoWP(commands, au::WorldModel::getInstance()->behaviours.wp);
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

  for (int i = 0; i < itemsNode.size(); i++)
  {
    QDomElement item = itemsNode.at(i).toElement();

    if (item.hasAttribute("name") && item.hasAttribute("alt") && item.hasAttribute("lon") && item.hasAttribute("lat"))
    {
      wp.append(
        au::WayPoint(item.attribute("lat").toFloat(), item.attribute("lon").toFloat(),
        item.attribute("alt").toInt()));
      std::cout << item.attribute("lat").toFloat() << std::endl << item.attribute("lon").toFloat() << std::endl
        << item.attribute("alt").toInt() << std::endl;
    }
  }

  return true;

}

void UserInterface::Parser::do_start_mission()
{
  au::WorldModel::getInstance()->init();
  au::WorldModel::getInstance()->behaviours.gotoWp(au::WorldModel::getInstance()->itr->lat,
    au::WorldModel::getInstance()->itr->lon,
    au::WorldModel::getInstance()->itr->alt);
  au::WorldModel::getInstance()->start_mission = true;
}

void UserInterface::Parser::do_land_mode()
{
  au::WorldModel::getInstance()->behaviours.landMode();
  doWrite = false;
}

void UserInterface::Parser::do_rtl_mode()
{
  au::WorldModel::getInstance()->behaviours.rtlMode();
  doWrite = false;
}