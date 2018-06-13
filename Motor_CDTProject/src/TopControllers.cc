
#include "TopControllers.hh"

#include "Controller.hh"
#include "MotorDriver.hh"
#include "TemperatureSensor.hh"
#include "Top.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static Capsule_Top top( &Top, &Top_slots[InstId_Top], NULL, NULL, true );

static UMLRTSlot * slots_Top[] = 
{
    &Top_slots[InstId_Top_controller],
    &Top_slots[InstId_Top_motorDriver],
    &Top_slots[InstId_Top_temperatureSensor]
};

static UMLRTCapsulePart parts_Top[] = 
{
    {
        &Top,
        Capsule_Top::part_controller,
        1,
        &slots_Top[0]
    },
    {
        &Top,
        Capsule_Top::part_motorDriver,
        1,
        &slots_Top[1]
    },
    {
        &Top,
        Capsule_Top::part_temperatureSensor,
        1,
        &slots_Top[2]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Top_controller[] = 
{
    {
        0,
        &borderports_Top_motorDriver[Capsule_MotorDriver::borderport_engine]
    },
    {
        0,
        &borderports_Top_temperatureSensor[Capsule_TemperatureSensor::borderport_sensoring]
    }
};

UMLRTCommsPort borderports_Top_controller[] = 
{
    {
        &Controller,
        Capsule_Controller::borderport_engine,
        &Top_slots[InstId_Top_controller],
        1,
        borderfarEndList_Top_controller,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        &Controller,
        Capsule_Controller::borderport_sensoring,
        &Top_slots[InstId_Top_controller],
        1,
        &borderfarEndList_Top_controller[1],
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_controller_ptrs[] = 
{
    &borderports_Top_controller[0],
    &borderports_Top_controller[1]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_controller[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_controller[] = 
{
    {
        &Controller,
        Capsule_Controller::internalport_timer,
        &Top_slots[InstId_Top_controller],
        1,
        &internalfarEndList_Top_controller[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &Controller,
        Capsule_Controller::internalport_log,
        &Top_slots[InstId_Top_controller],
        1,
        internalfarEndList_Top_controller,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_controller_ptrs[] = 
{
    &internalports_Top_controller[0],
    &internalports_Top_controller[1]
};

static Capsule_Controller top_controller( &Controller, &Top_slots[InstId_Top_controller], borderports_Top_controller_ptrs, internalports_Top_controller_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_motorDriver[] = 
{
    {
        0,
        &borderports_Top_controller[Capsule_Controller::borderport_engine]
    }
};

UMLRTCommsPort borderports_Top_motorDriver[] = 
{
    {
        &MotorDriver,
        Capsule_MotorDriver::borderport_engine,
        &Top_slots[InstId_Top_motorDriver],
        1,
        borderfarEndList_Top_motorDriver,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_motorDriver_ptrs[] = 
{
    &borderports_Top_motorDriver[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_motorDriver[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_motorDriver[] = 
{
    {
        &MotorDriver,
        Capsule_MotorDriver::internalport_timer,
        &Top_slots[InstId_Top_motorDriver],
        1,
        &internalfarEndList_Top_motorDriver[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &MotorDriver,
        Capsule_MotorDriver::internalport_log,
        &Top_slots[InstId_Top_motorDriver],
        1,
        internalfarEndList_Top_motorDriver,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_motorDriver_ptrs[] = 
{
    &internalports_Top_motorDriver[0],
    &internalports_Top_motorDriver[1]
};

static Capsule_MotorDriver top_motorDriver( &MotorDriver, &Top_slots[InstId_Top_motorDriver], borderports_Top_motorDriver_ptrs, internalports_Top_motorDriver_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_temperatureSensor[] = 
{
    {
        0,
        &borderports_Top_controller[Capsule_Controller::borderport_sensoring]
    }
};

UMLRTCommsPort borderports_Top_temperatureSensor[] = 
{
    {
        &TemperatureSensor,
        Capsule_TemperatureSensor::borderport_sensoring,
        &Top_slots[InstId_Top_temperatureSensor],
        1,
        borderfarEndList_Top_temperatureSensor,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_temperatureSensor_ptrs[] = 
{
    &borderports_Top_temperatureSensor[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_temperatureSensor[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_temperatureSensor[] = 
{
    {
        &TemperatureSensor,
        Capsule_TemperatureSensor::internalport_timer,
        &Top_slots[InstId_Top_temperatureSensor],
        1,
        &internalfarEndList_Top_temperatureSensor[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &TemperatureSensor,
        Capsule_TemperatureSensor::internalport_log,
        &Top_slots[InstId_Top_temperatureSensor],
        1,
        internalfarEndList_Top_temperatureSensor,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_temperatureSensor_ptrs[] = 
{
    &internalports_Top_temperatureSensor[0],
    &internalports_Top_temperatureSensor[1]
};

static Capsule_TemperatureSensor top_temperatureSensor( &TemperatureSensor, &Top_slots[InstId_Top_temperatureSensor], borderports_Top_temperatureSensor_ptrs, internalports_Top_temperatureSensor_ptrs, true );

UMLRTSlot Top_slots[] = 
{
    {
        "Top",
        0,
        &Top,
        NULL,
        0,
        &top,
        &DefaultController_,
        3,
        parts_Top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Top.controller",
        0,
        &Controller,
        &Top,
        Capsule_Top::part_controller,
        &top_controller,
        &DefaultController_,
        0,
        NULL,
        2,
        borderports_Top_controller,
        NULL,
        true,
        false
    },
    {
        "Top.motorDriver",
        0,
        &MotorDriver,
        &Top,
        Capsule_Top::part_motorDriver,
        &top_motorDriver,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_motorDriver,
        NULL,
        true,
        false
    },
    {
        "Top.temperatureSensor",
        0,
        &TemperatureSensor,
        &Top,
        Capsule_Top::part_temperatureSensor,
        &top_temperatureSensor,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_temperatureSensor,
        NULL,
        true,
        false
    }
};

