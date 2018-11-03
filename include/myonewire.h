
#include <OWBus.h>
#include <OWBus/OWDevice.h>

#if 0	/* Test bits ordering */
#define IMPLEMENT_BITFIELD_TEST
#endif
#include <OWBus/DS2406.h>

#define ONE_WIRE_BUS 10			// Where 1-wire bus is connected to (GPIO-5)
OneWire oneWire(ONE_WIRE_BUS);	// Initialize oneWire library
OWBus bus(&oneWire);



void myonewire_setup(){
    //discoverOneWireDevices();
}

void myonewire_loop(){
	Serial.print("\nNumber of probes on the bus :");
	Serial.println(bus.getDeviceCount());

	Serial.println("Individual address :");
	OWBus::Address addr;
	bus.search_reset();
	while( bus.search_next( addr ) ){
		Serial.print( addr.toString().c_str() );
		Serial.print(" : ");
		if(!addr.isValid( &oneWire))
			Serial.println("Invalid address");
		else {
			switch( addr.getFamilyCode() ){
			case DS2406::FAMILY_CODE: {
					DS2406 probe( bus, addr );
					Serial.println( probe.getFamily() );
#			ifdef IMPLEMENT_BITFIELD_TEST
					Serial.println( probe.checkArchitecture() ? "\tArch ok":"Bad bits ordering");
#			endif
					Serial.println( probe.hasPIOB() ? "\tBoth PIO.A & PIO.B" : "\tonly PIO.A" );
					Serial.println( probe.isParasitePowered() ? "\tParasite" : "\tExternal" );
				}
				break;
			default: {
					OWDevice probe( bus, addr );
					Serial.println( probe.getFamily() );
					Serial.println( probe.isParasitePowered() ? "\tParasite" : "\tExternal" );
				}
			}
		}
	}

	delay(10000);	// Sleep for 30 seconds


}