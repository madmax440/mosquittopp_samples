/**
 * @brief - implements mosquitto mqtt subscriber
 *
 * @copyright - 2020-present All rights reserved Devendra Naga (devendra.aaru@outlook.com)
 */
#include <iostream>
#include <string>
#include <string.h>
#include <mosquittopp.h>

class mosq_subscriber : public mosqpp::mosquittopp {
	public:
		explicit mosq_subscriber() {
			int ret = mosqpp::lib_init();
			if (ret != 0) {
				throw std::runtime_error("failed to init\n");
			}

			ret = mosqpp::mosquittopp::connect("localhost", 1883, 60);
			if (ret < 0) {
				throw std::runtime_error("failed to connect\n");
			}

			ret = mosqpp::mosquittopp::subscribe(nullptr, "/pub", 0);
			if (ret < 0) {
				throw std::runtime_error("failed to subscribe on /pub");
			}
		}

		~mosq_subscriber() {
			mosqpp::lib_cleanup();
		}

		void on_subscribe(int mid, int qos_count, int *granted_qos) {
			printf("mid: %d qos: %d\n", mid, qos_count);
		}

		void on_connect(int rc) {
			printf("connect res: %d\n", rc);
		}

		void on_message(const struct mosquitto_message *msg) {
			printf("received message %s len %d\n", (char *)msg->payload, msg->payloadlen);
		}

		void run() {
			while (1) {
				int ret = mosqpp::mosquittopp::loop();
				if (ret) {
					mosqpp::mosquittopp::reconnect();
				}
			}
		}
};

int main()
{
	mosq_subscriber mqtt;

	mqtt.run();
}
