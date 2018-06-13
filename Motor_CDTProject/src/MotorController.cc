
#include "MotorController.hh"

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

Capsule_MotorController::Capsule_MotorController( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
, timer( internalPorts[internalport_timer] )
, DELAY( 10000000 )
{
    stateNames[Second_step] = "Second_step";
    stateNames[First_step] = "First_step";
    stateNames[Fourth_step] = "Fourth_step";
    stateNames[Second_step__boundary] = "Second_step__boundary";
    stateNames[Third_step] = "Third_step";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
    int i = 0;
    while( i < 1 )
        history[i++] = SPECIAL_INTERNAL_STATE_UNVISITED;
}


void Capsule_MotorController::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case First_step:
        currentState = state_____First_step( &message );
        break;
    case Third_step:
        currentState = state_____Third_step( &message );
        break;
    case Fourth_step:
        currentState = state_____Fourth_step( &message );
        break;
    case Second_step__boundary:
        currentState = state_____Second_step__boundary( &message );
        break;
    default:
        break;
    }
}

void Capsule_MotorController::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = First_step;
}

const char * Capsule_MotorController::getCurrentStateString() const
{
    return stateNames[currentState];
}





void Capsule_MotorController::save_history( Capsule_MotorController::State compositeState, Capsule_MotorController::State subState )
{
    history[compositeState] = subState;
}

bool Capsule_MotorController::check_history( Capsule_MotorController::State compositeState, Capsule_MotorController::State subState )
{
    return history[compositeState] == subState;
}

void Capsule_MotorController::update_state( Capsule_MotorController::State newState )
{
    currentState = newState;
}

void Capsule_MotorController::entryaction_____First_step( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorController::First step entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    log.show("- * - *\n");
    digitalWrite(0, 0);
    digitalWrite(1, 1);
    digitalWrite(2, 0);
    digitalWrite(3, 1);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorController::entryaction_____Fourth_step( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorController::Fourth step entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    log.show("* - * -\n");
    digitalWrite(0, 1);
    digitalWrite(1, 0);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorController::entryaction_____Second_step( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorController::Second step entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    log.show("- * * -\n");
    digitalWrite(0, 0);
    digitalWrite(1, 1);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorController::entryaction_____Third_step( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorController::Third step entry  */
    timer.informIn(UMLRTTimespec(0,DELAY));
    log.show("* - * -\n");
    digitalWrite(0, 1);
    digitalWrite(1, 0);
    digitalWrite(2, 1);
    digitalWrite(3, 0);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorController::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Motor/Motor.uml Motor::MotorController transition subvertex0,First step */
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_MotorController::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( First_step );
    entryaction_____First_step( msg );
}

void Capsule_MotorController::actionchain_____Second_step__new_transition_1_to_unvisited_boundary( const UMLRTMessage * msg )
{
    update_state( Second_step__boundary );
}

void Capsule_MotorController::actionchain_____Second_step__new_transition_2_to_visited_boundary( const UMLRTMessage * msg )
{
    update_state( Second_step__boundary );
}

void Capsule_MotorController::actionchain_____Second_step__new_transition_3( const UMLRTMessage * msg )
{
    update_state( Second_step );
    save_history( Second_step, Second_step__boundary );
}

void Capsule_MotorController::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( Second_step );
    entryaction_____Second_step( msg );
}

void Capsule_MotorController::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( Third_step );
    entryaction_____Third_step( msg );
}

void Capsule_MotorController::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( Fourth_step );
    entryaction_____Fourth_step( msg );
}

void Capsule_MotorController::actionchain_____transition4( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( First_step );
    entryaction_____First_step( msg );
}

Capsule_MotorController::State Capsule_MotorController::junction_____Second_step__connectionPoint1( const UMLRTMessage * msg )
{
    actionchain_____transition2( msg );
    return Third_step;
}

Capsule_MotorController::State Capsule_MotorController::choice_____Second_step__deephistory( const UMLRTMessage * msg )
{
    if( check_history( Second_step, SPECIAL_INTERNAL_STATE_UNVISITED ) )
    {
        actionchain_____Second_step__new_transition_1_to_unvisited_boundary( msg );
        return Second_step__boundary;
    }
    else if( check_history( Second_step, Second_step__boundary ) )
    {
        actionchain_____Second_step__new_transition_2_to_visited_boundary( msg );
        return Second_step__boundary;
    }
    return currentState;
}

Capsule_MotorController::State Capsule_MotorController::state_____First_step( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition1( msg );
            return choice_____Second_step__deephistory( msg );
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

Capsule_MotorController::State Capsule_MotorController::state_____Fourth_step( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition4( msg );
            return First_step;
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

Capsule_MotorController::State Capsule_MotorController::state_____Second_step__boundary( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____Second_step__new_transition_3( msg );
            return junction_____Second_step__connectionPoint1( msg );
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

Capsule_MotorController::State Capsule_MotorController::state_____Third_step( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition3( msg );
            return Fourth_step;
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





void Capsule_MotorController::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_MotorController::unbindPort( bool isBorder, int portId, int index )
{
}



static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_MotorController::port_timer,
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
        Capsule_MotorController::port_log,
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

static void instantiate_MotorController( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &MotorController );
    slot->capsule = new Capsule_MotorController( &MotorController, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass MotorController = 
{
    "MotorController",
    NULL,
    instantiate_MotorController,
    0,
    NULL,
    0,
    NULL,
    2,
    portroles_internal
};

