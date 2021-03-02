#pragma once
#ifndef _EMAIL_H_
#define _EMAIL_H_

#include <Arduino.h>
#include "user_config.h"
#include <SD.h>

#ifdef ESP8266
#include <Ethernet.h>
#endif

#include <ESP_Mail_Client.h>

class EmailNotifier
{
private:
    SMTPSession smtp;
    ESP_Mail_Session session;

    void smtpCallback(SMTP_Status status);
public:
    void sendMail(const char *subject, const char *mailBody);
    void Init();
};


#endif