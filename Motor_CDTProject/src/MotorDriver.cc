
#include "MotorDriver.hh"

#include "Engine.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

#include <wiringPi.h>

Capsule_MotorDriver::Capsule_MotorDriver( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, engine( borderPorts[borderport_engine] )
, timer( internalPorts[internalport_timer] )
, DELAY( 5000000 )
, turns( 800 )
, totalTurns( 800 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[cnd_step_up] = "cnd_step_up";
    stateNames[cst_step_down] = "cst_step_down";
    stateNames[cst_step_up] = "cst_step_up";
    stateNames[cnd_step_down] = "cnd_step_down";
    stateNames[cnd_step_up__boundary] = "cnd_step_up__boundary";
    stateNames[crd_step_down] = "crd_step_down";
    stateNames[crd_step_up] = "crd_step_up";
    stateNames[cth_step_down] = "cth_step_down";
    stateNames[cth_step_up] = "cth_step_up";
    stateNames[IDLE] = "IDLE";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 1 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}








void Capsule_MotorDriver::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, true );
            break;
        }
}

void Capsule_MotorDriver::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_engine:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_engine, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_engine], index );
            break;
        }
}




void Capsule_MotorDriver::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case cst_step_up:
        currentState = state_____cst_step_up( &message );
        break;
    case crd_step_up:
        currentState = state_____crd_step_up( &message );
        break;
    case cth_step_up:
        currentState = state_____cth_step_up( &message );
        break;
    case IDLE:
        currentState = state_____IDLE( &message );
        break;
    case cst_step_down:
        currentState = state_____cst_step_down( &message );
        break;
    case cnd_step_down:
        currentState = state_____cnd_step_down( &message );
        break;
    case crd_step_down:
        currentState = state_____crd_step_down( &message );
        break;
    case cth_step_down:
        currentState = state_____cth_step_down( &message );
        break;
    case cnd_step_up__boundary:
        currentState = state_____cnd_step_up__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_MotorDriver::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = IDLE;
}

const char * Capsule_MotorDriver::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_MotorDriver::save_history( Capsule_MotorDriver::State compositeState, Capsule_MotorDriver::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_MotorDriver::check_history( Capsule_MotorDriver::State compositeState, Capsule_MotorDriver::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_MotorDriver::update_state( Capsule_MotorDriver::State newState )
{
    currentState = newState;
}

void Capsule_MotorDriver::entryaction_____IDLE( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::IDLE entry  */
    //engine.isIdle().send();
    turns = totalTurns;
    digitalWrite(0, 0);
    digitalWrite(1, 0);
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____cnd_step_down( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::2nd step down entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    digitalWrite(0, 1);
    digitalWrite(1, 0);
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____cnd_step_up( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::2nd step up entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    digitalWrite(0, 0);
    digitalWrite(1, 1);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____crd_step_down( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::3rd step down entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    digitalWrite(0, 1);
    digitalWrite(1, 0);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____crd_step_up( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::3rd step up entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    digitalWrite(0, 1);
    digitalWrite(1, 0);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____cst_step_down( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::1st step down entry  */
    turns--;
    if(turns > 0)
    timer.informIn(UMLRTTimespec(0,DELAY));
    else
    engine.stopping().send();
    digitalWrite(0, 0);
    digitalWrite(1, 1);
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____cst_step_up( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::1st step up entry  */
    turns--;
    if(turns > 0)
    timer.informIn(UMLRTTimespec(0,DELAY));
    else
    engine.stopping().send();
    digitalWrite(0, 0);
    digitalWrite(1, 1);
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____cth_step_down( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::4th step down entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    digitalWrite(0, 0);
    digitalWrite(1, 1);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::entryaction_____cth_step_up( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver::4th step up entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    digitalWrite(0, 1);
    digitalWrite(1, 0);
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorDriver transition subvertex0,IDLE */
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorDriver::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( IDLE );
    entryaction_____IDLE( msg );
}

void Capsule_MotorDriver::actionchain_____cnd_step_up__new_transition_1_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( cnd_step_up__boundary );
}

void Capsule_MotorDriver::actionchain_____cnd_step_up__new_transition_2_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( cnd_step_up__boundary );
}

void Capsule_MotorDriver::actionchain_____cnd_step_up__new_transition_3( const UMLRTMessage * msg )
{
    update_state( cnd_step_up );
    save_history( cnd_step_up, cnd_step_up__boundary );
}

void Capsule_MotorDriver::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cth_step_up );
    entryaction_____cth_step_up( msg );
}

void Capsule_MotorDriver::actionchain_____transition10( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( IDLE );
    entryaction_____IDLE( msg );
}

void Capsule_MotorDriver::actionchain_____transition11( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cnd_step_up );
    entryaction_____cnd_step_up( msg );
}

void Capsule_MotorDriver::actionchain_____transition12( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( crd_step_up );
    entryaction_____crd_step_up( msg );
}

void Capsule_MotorDriver::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cst_step_up );
    entryaction_____cst_step_up( msg );
}

void Capsule_MotorDriver::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cst_step_up );
    entryaction_____cst_step_up( msg );
}

void Capsule_MotorDriver::actionchain_____transition4( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( IDLE );
    entryaction_____IDLE( msg );
}

void Capsule_MotorDriver::actionchain_____transition5( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cnd_step_down );
    entryaction_____cnd_step_down( msg );
}

void Capsule_MotorDriver::actionchain_____transition6( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( crd_step_down );
    entryaction_____crd_step_down( msg );
}

void Capsule_MotorDriver::actionchain_____transition7( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cth_step_down );
    entryaction_____cth_step_down( msg );
}

void Capsule_MotorDriver::actionchain_____transition8( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cst_step_down );
    entryaction_____cst_step_down( msg );
}

void Capsule_MotorDriver::actionchain_____transition9( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( cst_step_down );
    entryaction_____cst_step_down( msg );
}

Capsule_MotorDriver::State Capsule_MotorDriver::junction_____cnd_step_up__new_exitpoint_1( const UMLRTMessage * msg )
{
    actionchain_____transition12( msg );
    return crd_step_up;
}

Capsule_MotorDriver::State Capsule_MotorDriver::choice_____cnd_step_up__deephistory( const UMLRTMessage * msg )
{
    if( check_history( cnd_step_up, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____cnd_step_up__new_transition_1_to_unvisited_boundary( msg );
        return cnd_step_up__boundary;
    }
    else if( check_history( cnd_step_up, cnd_step_up__boundary ) )
    {
        actionchain_____cnd_step_up__new_transition_2_to_visited_boundary( msg );
        return cnd_step_up__boundary;
    }
    return currentState;
}

Capsule_MotorDriver::State Capsule_MotorDriver::state_____IDLE( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_moveUpwards:
            actionchain_____transition3( msg );
            return cst_step_up;
        case Engine::signal_moveDownwards:
            actionchain_____transition8( msg );
            return cst_step_down;
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____cnd_step_down( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition6( msg );
            return crd_step_down;
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____cnd_step_up__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____cnd_step_up__new_transition_3( msg );
            return junction_____cnd_step_up__new_exitpoint_1( msg );
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____crd_step_down( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition7( msg );
            return cth_step_down;
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____crd_step_up( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition1( msg );
            return cth_step_up;
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____cst_step_down( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition5( msg );
            return cnd_step_down;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stopped:
            actionchain_____transition10( msg );
            return IDLE;
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____cst_step_up( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_engine:
        switch( msg->getSignalId() )
        {
        case Engine::signal_stopped:
            actionchain_____transition4( msg );
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
            actionchain_____transition11( msg );
            return choice_____cnd_step_up__deephistory( msg );
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____cth_step_down( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition9( msg );
            return cst_step_down;
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

Capsule_MotorDriver::State Capsule_MotorDriver::state_____cth_step_up( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition2( msg );
            return cst_step_up;
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
        Capsule_MotorDriver::port_engine,
        "Engine",
        "engine",
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
        Capsule_MotorDriver::port_timer,
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
        Capsule_MotorDriver::port_log,
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

static void instantiate_MotorDriver( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &MotorDriver );
    slot->capsule = new Capsule_MotorDriver( &MotorDriver, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass MotorDriver = 
{
    "MotorDriver",
    NULL,
    instantiate_MotorDriver,
    0,
    NULL,
    1,
    portroles_border,
    2,
    portroles_internal
};

