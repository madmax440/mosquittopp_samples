project(mqtt_samples)

cmake_minimum_required(VERSION 3.8)

set(MQTT_PUB_SRC
		./mosq_pub.cc)

set(MQTT_SUB_SRC
		./mosq_sub.cc)

add_executable(mosq_pub ${MQTT_PUB_SRC})
target_link_libraries(mosq_pub pthread mosquittopp)

add_executable(mosq_sub ${MQTT_SUB_SRC})
target_link_libraries(mosq_sub pthread mosquittopp)
