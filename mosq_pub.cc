/**
 * @brief - implements mosquitto mqtt publisher
 *
 * @copyright - 2020-present All rights reserved Devendra Naga (devendra.aaru@outlook.com)
 */
#include <iostream>
#include <string>
#include <string.h>
#include <thread>
#include<mosquittopp.h>

int main()
{
	int ret = mosqpp::lib_init();
	if (ret != 0) {
		return -1;
	}

	mosqpp::mosquittopp mqtt;

	ret = mqtt.connect("localhost");
	if (ret != 0) {
		return -1;
	}

	while (1) {
		const char *msg = "hello from mqtt publisher";
		std::this_thread::sleep_for(std::chrono::seconds(1));

		mqtt.publish(nullptr, "/pub", strlen(msg), msg, 0, false);
	}
}
