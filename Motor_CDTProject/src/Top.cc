
#include "Top.hh"

#include "Controller.hh"
#include "MotorDriver.hh"
#include "TemperatureSensor.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
class UMLRTRtsInterface;

Capsule_Top::Capsule_Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, controller( &slot->parts[part_controller] )
, motorDriver( &slot->parts[part_motorDriver] )
, temperatureSensor( &slot->parts[part_temperatureSensor] )
{
}





void Capsule_Top::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Top::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "controller",
        &Controller,
        1,
        1,
        false,
        false
    },
    {
        "motorDriver",
        &MotorDriver,
        1,
        1,
        false,
        false
    },
    {
        "temperatureSensor",
        &TemperatureSensor,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_controller].slots[0]->ports[Capsule_Controller::borderport_engine], 0, &slot->parts[Capsule_Top::part_motorDriver].slots[0]->ports[Capsule_MotorDriver::borderport_engine], 0 );
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_controller].slots[0]->ports[Capsule_Controller::borderport_sensoring], 0, &slot->parts[Capsule_Top::part_temperatureSensor].slots[0]->ports[Capsule_TemperatureSensor::borderport_sensoring], 0 );
    Controller.instantiate( NULL, slot->parts[Capsule_Top::part_controller].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_controller].slots[0], Controller.numPortRolesBorder ) );
    MotorDriver.instantiate( NULL, slot->parts[Capsule_Top::part_motorDriver].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_motorDriver].slots[0], MotorDriver.numPortRolesBorder ) );
    TemperatureSensor.instantiate( NULL, slot->parts[Capsule_Top::part_temperatureSensor].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_temperatureSensor].slots[0], TemperatureSensor.numPortRolesBorder ) );
    slot->capsule = new Capsule_Top( &Top, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Top = 
{
    "Top",
    NULL,
    instantiate_Top,
    3,
    roles,
    0,
    NULL,
    0,
    NULL
};

