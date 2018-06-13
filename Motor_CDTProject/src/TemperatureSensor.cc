
#include "TemperatureSensor.hh"

#include "Sensoring.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_TemperatureSensor::Capsule_TemperatureSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, sensoring( borderPorts[borderport_sensoring] )
, timer( internalPorts[internalport_timer] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[DETECTING] = "DETECTING";
    stateNames[IDLE] = "IDLE";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}








void Capsule_TemperatureSensor::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_sensoring:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_sensoring, index, true );
            break;
        }
}

void Capsule_TemperatureSensor::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_sensoring:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_sensoring, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_sensoring], index );
            break;
        }
}

void Capsule_TemperatureSensor::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case IDLE:
        currentState = state_____IDLE( &message );
        break;
    case DETECTING:
        currentState = state_____DETECTING( &message );
        break;
    default:
        break;
    }
}

void Capsule_TemperatureSensor::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = IDLE;
}

const char * Capsule_TemperatureSensor::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_TemperatureSensor::update_state( Capsule_TemperatureSensor::State newState )
{
    currentState = newState;
}

void Capsule_TemperatureSensor::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::TemperatureSensor::IDLE entry  */
    log.show("Temperature sensor is idle\n");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_TemperatureSensor::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::TemperatureSensor transition subvertex0,IDLE */
    system("sudo modprobe w1-gpio");
    system("sudo modprobe w1-therm");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_TemperatureSensor::transitionaction_____detecting( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::TemperatureSensor transition DETECTING,DETECTING,timeout:timer */
    int SIZE = 1;
    int NUMELEM = 74;
    FILE *fp = NULL;
    char buff[100];
    char temp_raw[5];
    memset(buff,0,sizeof(buff));
    int temperature = 0;
    fp = fopen("/sys/bus/w1/devices/28-80000003a0e1/w1_slave","r");
    if (NULL == fp)
    {
    printf("\n fopen Error!!!\n\n");
    exit(1);
    }
    if(SIZE*NUMELEM != fread(buff,SIZE,NUMELEM,fp))
    {
    printf("\n fread() failed\n");
    exit(1);
    }
    temp_raw[0] = buff[69];
    temp_raw[1] = buff[70];
    temp_raw[2] = buff[71];
    temp_raw[3] = buff[72];
    temp_raw[4] = buff[73];
    temp_raw[5] = buff[74];
    temperature = atoll(temp_raw);
    log.log("\nTemp Is: %4.3f DegC\n", (float)temperature/1000 );
    sensoring.sendData((float)temperature/1000).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_TemperatureSensor::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::TemperatureSensor transition IDLE,DETECTING,startSensor:sensoring */
    log.log("start detecting");
    timer.informIn(UMLRTTimespec(0,10000));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_TemperatureSensor::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::TemperatureSensor transition DETECTING,IDLE,stopSensor:sensoring */
    log.log("stop detecting");
    sensoring.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_TemperatureSensor::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( IDLE );
    entryaction_____IDLE( msg );
}

void Capsule_TemperatureSensor::actionchain_____detecting( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____detecting( msg );
    update_state( DETECTING );
}

void Capsule_TemperatureSensor::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( DETECTING );
}

void Capsule_TemperatureSensor::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( IDLE );
    entryaction_____IDLE( msg );
}

Capsule_TemperatureSensor::State Capsule_TemperatureSensor::state_____DETECTING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_sensoring:
        switch( msg->getSignalId() )
        {
        case Sensoring::signal_stopSensor:
            actionchain_____transition2( msg );
            return IDLE;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____detecting( msg );
            return DETECTING;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_TemperatureSensor::State Capsule_TemperatureSensor::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_sensoring:
        switch( msg->getSignalId() )
        {
        case Sensoring::signal_startSensor:
            actionchain_____transition1( msg );
            return DETECTING;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_TemperatureSensor::port_sensoring,
        "Sensoring",
        "sensoring",
        "",
        1,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_TemperatureSensor::port_timer,
        "Timing",
        "timer",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_TemperatureSensor::port_log,
        "Log",
        "log",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_TemperatureSensor( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &TemperatureSensor );
    slot->capsule = new Capsule_TemperatureSensor( &TemperatureSensor, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass TemperatureSensor = 
{
    "TemperatureSensor",
    NULL,
    instantiate_TemperatureSensor,
    0,
    NULL,
    1,
    portroles_border,
    2,
    portroles_internal
};

