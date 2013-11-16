#
# RFCOMM configuration file.
#

rfcomm0 {
	# Automatically bind the device at startup
	bind yes;

	# Bluetooth address of the device
	device 20:13:08:08:18:81;

	# RFCOMM channel for the connection
	channel	1;

	# Description of the connection
	comment "WaterBunny / NanoQuad";
}






sudo rfcomm connect 0
