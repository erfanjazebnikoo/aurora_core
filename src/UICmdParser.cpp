/*
 * UICmdParser.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: sajjadmuscle
 */

#include "UICmdParser.h"
#include <QStringList>
#include <QChar>
#include <iostream>

const QString TOKEN_MAVROS_STATE = "MavrosState";
const QString TOKEN_TAKE_OFF = "TakeOff";
const QString TOKEN_GUIDED_MODE = "GuidedMode";
const QString TOKEN_LAND_MODE = "LandMode";
const QString TOKEN_RTL_MODE = "RTLMode";
const QString TOKEN_ARM = "Arm";
const QString TOKEN_START_MISSION = "StartMission";
const QChar COMMAND_SEPARATOR = ';';

namespace au
{

const QString &UICmdParser::result() const
{
  return resultString;
}

void UICmdParser::clearResult()
{
  resultString.clear();
}

void UICmdParser::parse(const QString &commands)
{
  if (commands.length() > 100)
  {
    std::cout << commands.toStdString();
    do_fill_wayPoint(commands);
  }
  else
  {
    QStringList commandList = commands.split(COMMAND_SEPARATOR, QString::SkipEmptyParts);

    for (int i = 0; i < commandList.size(); i++)
    {
      lastCommand = commandList[i].trimmed();

      QStringList parts = lastCommand.split(QRegExp("\\s+"), QString::SkipEmptyParts);

      if (parts.size() > 0)
      {
        if (parts[0] == TOKEN_MAVROS_STATE)
        {
          do_mavros_state();
        }
        else if (parts[0] == TOKEN_TAKE_OFF)
        {
          do_take_off(parts[1]);
        }
        else if (parts[0] == TOKEN_GUIDED_MODE)
        {
          do_guided_mode();
        }
        else if (parts[0] == TOKEN_ARM)
        {
          do_arm();
        }
        else if (parts[0] == TOKEN_START_MISSION)
        {
          do_start_mission();
        }
        else if (parts[0] == TOKEN_LAND_MODE)
        {
          do_land_mode();
        }
        else if (parts[0] == TOKEN_RTL_MODE)
        {
          do_rtl_mode();
        }
      }
    }
  }
}

} /* namespace au */