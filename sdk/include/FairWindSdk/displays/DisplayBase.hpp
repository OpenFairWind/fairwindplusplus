//
// Created by Raffaele Montella on 05/06/21.
//

#ifndef FAIRWIND_DISPLAYBASE_HPP
#define FAIRWIND_DISPLAYBASE_HPP

#include <QString>
#include <FairWindSdk/FairWindSDK.hpp>

namespace fairwind::displays {
    class FAIRWINDSDK_LIB_DECL DisplayBase {

    public:
        DisplayBase();
        ~DisplayBase();

        virtual void setLabel(QString label) = 0;
        virtual void setUnits(QString units) = 0;
        virtual void setText(QString text) = 0;
        virtual void subscribe(QString fullPath);
        virtual void update(const QJsonObject update);

        QString getDstUnits() const;
        QString getFullPath() const;
        QString getSrcUnits() const;
        QString getDescription() const;
        QChar getFillChar() const;
        QChar getFormat() const;
        int getPrecision() const;
        int getFieldWidth() const;

        void setDstUnits(QString &units);
        void setSrcUnits(QString &srcUnits);
        void setDescription(QString &description);
        void setFillChar(QChar fillChar);
        void setFormat(QChar format);
        void setPrecision(int precision);
        void setFieldWidth(int fieldWidth);



    private:
        QString mDstUnits;
        QString mFullPath;
        QString mSrcUnits;
        QString mDescription;
        QChar mFillChar;
        QChar mFormat;
        int mPrecision;
        int mFieldWidth;
    };
}

#endif //FAIRWIND_DISPLAYBASE_HPP
