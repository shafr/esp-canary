#pragma once
#ifndef _CONSOLE_LOG_H_
#define _CONSOLE_LOG_H_

void consoleLogNotifyAttackOccurred(String attackerIpAddress);

void consoleLogResetAttackState();

void consoleLogNotify(String message);

#endif