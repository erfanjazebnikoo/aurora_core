/* 
 * @File:     UICmdResponse.cpp
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 22, 2016
 */

#include "UICmdResponse.h"
#include <QtXml/qdom.h>

namespace au
{
const QString TOKEN_RESPONSE = "response";
const QString TOKEN_CMD = "cmd";
const QString TOKEN_VER = "ver";
const QString TOKEN_ERR = "error";
const QString TOKEN_ITEM = "item";
const QString TOKEN_TYPE = "type";
const QString TOKEN_NAME = "name";
const QString TOKEN_DATA = "data";

bool UICmdResponse::fromXML(const QString xml)
{
  version = "";
  command = "";
  items.clear();

  QDomDocument doc;
  doc.setContent(xml);

  QDomNodeList responseNode = doc.elementsByTagName(TOKEN_RESPONSE);

  if (responseNode.size() != 1)
    return false;

  QDomElement response = responseNode.at(0).toElement();

  if (!response.hasAttribute(TOKEN_VER) || !response.hasAttribute(TOKEN_CMD))
    return false;

  version = response.attribute(TOKEN_VER);
  command = response.attribute(TOKEN_CMD);

  if (response.hasAttribute(TOKEN_ERR))
    error = response.attribute(TOKEN_ERR).toInt();

  QDomNodeList itemsNode = doc.elementsByTagName(TOKEN_ITEM);

  for (int i = 0; i < itemsNode.size(); i++)
  {
    QDomElement item = itemsNode.at(i).toElement();

    if (item.hasAttribute(TOKEN_TYPE) && item.hasAttribute(TOKEN_NAME) && item.hasAttribute(TOKEN_DATA))
    {
      QString type = item.attribute(TOKEN_TYPE);

      if (type.size() < 1)
        continue;

      items.append(UICmdResponse::Item(type[0].toLatin1(), item.attribute(TOKEN_NAME), item.attribute(TOKEN_DATA)));
    }
  }

  return true;
}

QString UICmdResponse::toXML() const
{
  QDomDocument doc;

  QDomElement response = doc.createElement(TOKEN_RESPONSE);
  response.setAttribute(TOKEN_VER, version);
  response.setAttribute(TOKEN_CMD, command);
  response.setAttribute(TOKEN_ERR, error);

  for (auto itr = items.begin(); itr != items.end(); itr++)
  {
    QDomElement item = doc.createElement(TOKEN_ITEM);
    item.setAttribute(TOKEN_NAME, itr->name);
    item.setAttribute(TOKEN_DATA, itr->data);
    item.setAttribute(TOKEN_TYPE, itr->type);
    response.appendChild(item);
  }

  doc.appendChild(response);

  return doc.toString();
}

} /* namespace au */
