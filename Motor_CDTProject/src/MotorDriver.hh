
#ifndef MOTORDRIVER_HH
#define MOTORDRIVER_HH

#include "Engine.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
#include <stdint.h>
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_MotorDriver : public UMLRTCapsule
{
public:
    Capsule_MotorDriver( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Engine::Conj engine;
public:
    enum BorderPortId
    {
        borderport_engine
    };
protected:
    UMLRTLogProtocol_baserole log;
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
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    uint32_t DELAY;
    int turns;
    int totalTurns;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        cnd_step_up,
        cst_step_down,
        cst_step_up,
        cnd_step_down,
        cnd_step_up__boundary,
        crd_step_down,
        crd_step_up,
        cth_step_down,
        cth_step_up,
        IDLE,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[12];
    State currentState;
    State history[1];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void update_state( State newState );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void entryaction_____cnd_step_down( const UMLRTMessage * msg );
    void entryaction_____cnd_step_up( const UMLRTMessage * msg );
    void entryaction_____crd_step_down( const UMLRTMessage * msg );
    void entryaction_____crd_step_up( const UMLRTMessage * msg );
    void entryaction_____cst_step_down( const UMLRTMessage * msg );
    void entryaction_____cst_step_up( const UMLRTMessage * msg );
    void entryaction_____cth_step_down( const UMLRTMessage * msg );
    void entryaction_____cth_step_up( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____cnd_step_up__new_transition_1_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____cnd_step_up__new_transition_2_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____cnd_step_up__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____transition1( const UMLRTMessage * msg );
    void actionchain_____transition10( const UMLRTMessage * msg );
    void actionchain_____transition11( const UMLRTMessage * msg );
    void actionchain_____transition12( const UMLRTMessage * msg );
    void actionchain_____transition2( const UMLRTMessage * msg );
    void actionchain_____transition3( const UMLRTMessage * msg );
    void actionchain_____transition4( const UMLRTMessage * msg );
    void actionchain_____transition5( const UMLRTMessage * msg );
    void actionchain_____transition6( const UMLRTMessage * msg );
    void actionchain_____transition7( const UMLRTMessage * msg );
    void actionchain_____transition8( const UMLRTMessage * msg );
    void actionchain_____transition9( const UMLRTMessage * msg );
    State junction_____cnd_step_up__new_exitpoint_1( const UMLRTMessage * msg );
    State choice_____cnd_step_up__deephistory( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
    State state_____cnd_step_down( const UMLRTMessage * msg );
    State state_____cnd_step_up__boundary( const UMLRTMessage * msg );
    State state_____crd_step_down( const UMLRTMessage * msg );
    State state_____crd_step_up( const UMLRTMessage * msg );
    State state_____cst_step_down( const UMLRTMessage * msg );
    State state_____cst_step_up( const UMLRTMessage * msg );
    State state_____cth_step_down( const UMLRTMessage * msg );
    State state_____cth_step_up( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass MotorDriver;

#endif

