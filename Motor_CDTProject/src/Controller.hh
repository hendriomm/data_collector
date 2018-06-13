
#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "Engine.hh"
#include "Sensoring.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_Controller : public UMLRTCapsule
{
public:
    Capsule_Controller( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Engine::Base engine;
public:
    enum BorderPortId
    {
        borderport_engine,
        borderport_sensoring
    };
protected:
    UMLRTLogProtocol_baserole log;
    Sensoring::Base sensoring;
    UMLRTTimerProtocol_baserole timer;
public:
    enum InternalPortId
    {
        internalport_timer,
        internalport_log
    };
    enum PartId
    {
    };
    enum PortId
    {
        port_engine,
        port_log,
        port_sensoring,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        FINISH_SENSORING,
        MOVE_DOWNWARDS,
        MOVE_UPWARDS,
        STAND_BY,
        START_SENSORING,
        WAITING,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[8];
    State currentState;
    void update_state( State newState );
    void entryaction_____FINISH_SENSORING( const UMLRTMessage * msg );
    void entryaction_____MOVE_DOWNWARDS( const UMLRTMessage * msg );
    void entryaction_____MOVE_UPWARDS( const UMLRTMessage * msg );
    void entryaction_____STAND_BY( const UMLRTMessage * msg );
    void entryaction_____START_SENSORING( const UMLRTMessage * msg );
    void entryaction_____WAITING( const UMLRTMessage * msg );
    void transitionaction_____transition2( const UMLRTMessage * msg );
    void transitionaction_____transition5( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____transition1( const UMLRTMessage * msg );
    void actionchain_____transition2( const UMLRTMessage * msg );
    void actionchain_____transition3( const UMLRTMessage * msg );
    void actionchain_____transition4( const UMLRTMessage * msg );
    void actionchain_____transition5( const UMLRTMessage * msg );
    void actionchain_____transition6( const UMLRTMessage * msg );
    State state_____FINISH_SENSORING( const UMLRTMessage * msg );
    State state_____MOVE_DOWNWARDS( const UMLRTMessage * msg );
    State state_____MOVE_UPWARDS( const UMLRTMessage * msg );
    State state_____STAND_BY( const UMLRTMessage * msg );
    State state_____START_SENSORING( const UMLRTMessage * msg );
    State state_____WAITING( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Controller;

#endif

