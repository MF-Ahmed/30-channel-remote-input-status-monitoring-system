# 30-channel-remote-input-status-monitoring-system

The 30 channel remote input status monitoring system is a microcontroller based data acquisition and displaying system for chiller and pumps status.
The system has 30 inputs/channels of 220VAC, 50Hz input status of 3 chillers and 6 pumps.
The system comprises of a Master and Slave module which communicate with each other via a serial RS-485 link.
The Master module is responsible for signal conditioning, data acquisition and transmitting to formatted data to slave along with checksum byte.
The Slave module receives the data form master and displays it on the panel.
Checksum error detection is incorporated in the communication protocol.
