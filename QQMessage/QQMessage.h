#pragma once
#include "Analyst.h"

static class QQMessage {
public:
	static void onOpen();
	static void onClose();
	static void onFail();

	static void readMessage(const std::string& message);

	static void _Init(std::string url = "127.0.0.1:6700");

	static void _Stop();
};

