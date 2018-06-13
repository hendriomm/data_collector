
#include "Controller.hh"

#include "Engine.hh"
#include "Sensoring.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtframeservice.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Controller::Capsule_Controller( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, engine( borderPorts[borderport_engine] )
, sensoring( borderPorts[borderport_sensoring] )
, timer( internalPorts[internalport_timer] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[FINISH_SENSORING] = "FINISH_SENSORING";
    stateNames[MOVE_DOWNWARDS] = "MOVE_DOWNWARDS";
    stateNames[MOVE_UPWARDS] = "MOVE_UPWARDS";
    stateNames[STAND_BY] = "STAND_BY";
    stateNames[START_SENSORING] = "START_SENSORING";
    stateNames[WAITING] = "WAITING";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}









void Capsule_Controller::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, true );
            break;
        case borderport_sensoring:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_sensoring, index, true );
            break;
        }
}

void Capsule_Controller::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_engine], index );
            break;
        case borderport_sensoring:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_sensoring, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_sensoring], index );
            break;
        }
}

void Capsule_Controller::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case STAND_BY:
        currentState = state_____STAND_BY( &message );
        break;
    case MOVE_DOWNWARDS:
        currentState = state_____MOVE_DOWNWARDS( &message );
        break;
    case START_SENSORING:
        currentState = state_____START_SENSORING( &message );
        break;
    case MOVE_UPWARDS:
        currentState = state_____MOVE_UPWARDS( &message );
        break;
    case FINISH_SENSORING:
        currentState = state_____FINISH_SENSORING( &message );
        break;
    case WAITING:
        currentState = state_____WAITING( &message );
        break;
    default:
        break;
    }
}

void Capsule_Controller::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = STAND_BY;
}

const char * Capsule_Controller::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Controller::update_state( Capsule_Controller::State newState )
{
    currentState = newState;
}

void Capsule_Controller::entryaction_____FINISH_SENSORING( const UMLRTMessage * msg )
{
    #define data ( *(double *)msg->getParam( 0 ) )
    #define rtdata ( (double *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller::FINISH SENSORING entry  */
    sensoring.stopSensor().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef data
}

void Capsule_Controller::entryaction_____MOVE_DOWNWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller::MOVE DOWNWARDS entry  */
    log.log ("**moving downwards");
    engine.moveDownwards().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Controller::entryaction_____MOVE_UPWARDS( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller::MOVE UPWARDS entry  */
    log.log ("**moving upwards");
    engine.moveUpwards().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Controller::entryaction_____STAND_BY( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller::STAND BY entry  */
    timer.informIn(UMLRTTimespec(8,0));
    log.log ("**Controller standing by");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Controller::entryaction_____START_SENSORING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller::START SENSORING entry  */
    sensoring.startSensor().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Controller::entryaction_____WAITING( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller::WAITING entry  */
    timer.informIn(UMLRTTimespec(4,0));
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Controller::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller transition MOVE DOWNWARDS,START SENSORING,stopping:engine */
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Controller::transitionaction_____transition5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::Controller transition MOVE UPWARDS,STAND BY,stopping:engine */
    engine.stopped().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Controller::actionchain_____Initial( const UMLRTMessage * msg )
{
    update_state( STAND_BY );
    entryaction_____STAND_BY( msg );
}

void Capsule_Controller::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( MOVE_DOWNWARDS );
    entryaction_____MOVE_DOWNWARDS( msg );
}

void Capsule_Controller::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( START_SENSORING );
    entryaction_____START_SENSORING( msg );
}

void Capsule_Controller::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( FINISH_SENSORING );
    entryaction_____FINISH_SENSORING( msg );
}

void Capsule_Controller::actionchain_____transition4( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( WAITING );
    entryaction_____WAITING( msg );
}

void Capsule_Controller::actionchain_____transition5( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition5( msg );
    update_state( STAND_BY );
    entryaction_____STAND_BY( msg );
}

void Capsule_Controller::actionchain_____transition6( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( MOVE_UPWARDS );
    entryaction_____MOVE_UPWARDS( msg );
}

Capsule_Controller::State Capsule_Controller::state_____FINISH_SENSORING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_sensoring:
        switch( msg->getSignalId() )
        {
        case Sensoring::signal_stopped:
            actionchain_____transition4( msg );
            return WAITING;
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

Capsule_Controller::State Capsule_Controller::state_____MOVE_DOWNWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stopping:
            actionchain_____transition2( msg );
            return START_SENSORING;
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

Capsule_Controller::State Capsule_Controller::state_____MOVE_UPWARDS( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stopping:
            actionchain_____transition5( msg );
            return STAND_BY;
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

Capsule_Controller::State Capsule_Controller::state_____STAND_BY( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition1( msg );
            return MOVE_DOWNWARDS;
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

Capsule_Controller::State Capsule_Controller::state_____START_SENSORING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_sensoring:
        switch( msg->getSignalId() )
        {
        case Sensoring::signal_sendData:
            actionchain_____transition3( msg );
            return FINISH_SENSORING;
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

Capsule_Controller::State Capsule_Controller::state_____WAITING( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition6( msg );
            return MOVE_UPWARDS;
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
        Capsule_Controller::port_engine,
        "Engine",
        "engine",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    },
    {
        Capsule_Controller::port_sensoring,
        "Sensoring",
        "sensoring",
        "",
        1,
        true,
        false,
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
        Capsule_Controller::port_timer,
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
        Capsule_Controller::port_log,
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

static void instantiate_Controller( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Controller );
    slot->capsule = new Capsule_Controller( &Controller, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Controller = 
{
    "Controller",
    NULL,
    instantiate_Controller,
    0,
    NULL,
    2,
    portroles_border,
    2,
    portroles_internal
};

