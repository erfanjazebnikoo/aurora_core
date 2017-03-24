/* 
 * @File:     UICmdResponse.h
 * @Author:   Sajjad Rahnama
 * 
 * @Project:  Aurora
 * @Version:  1.0 - Iran Open 2017
 * 
 * @Created on Dec 22, 2016
 */

#ifndef UICMDRESPONSE_H_
#define UICMDRESPONSE_H_

#include <QString>
#include <QList>

namespace au {

    class UICmdResponse {
    public:

        class Item {
        public:

            char type;
            QString name;
            QString data;

            Item() {
            }

            Item(char t, const QString &n, const QString &d) :
            type(t), name(n), data(d) {
            }
        };

        enum Error {
            E_OK = 0, E_BAD_COMMAND, E_INTERNAL_ERR
        };

        enum TypeCode {
            TYPE_CODE_NONE = 0, TYPE_CODE_INTEGER = 1, TYPE_CODE_BOOLEAN = 2, TYPE_CODE_STRING = 3, TYPE_CODE_FLOAT = 4
        };

        typedef QList<Item> Items;

        UICmdResponse() {
        }

        UICmdResponse(const QString &xml) {
            fromXML(xml);
        }

        UICmdResponse(const QString &v, const QString &c, int e) :
        version(v), command(c), error(e) {
        }

        UICmdResponse(const QString &v, const QString &c, int e, const Items &i) :
        version(v), command(c), error(e), items(i) {
        }

        QString version;
        QString command;
        int error;
        Items items;

        bool fromXML(const QString xml);
        QString toXML() const;
    };

} /* namespace au */

#endif /* UICMDRESPONSE_H_ */
