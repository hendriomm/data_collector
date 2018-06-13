
#ifndef MOTORCONTROLLER_HH
#define MOTORCONTROLLER_HH

#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
#include <stdint.h>
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_MotorController : public UMLRTCapsule
{
public:
    Capsule_MotorController( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
    enum PortId
    {
        port_log,
        port_timer
    };
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Second_step,
        First_step,
        Fourth_step,
        Second_step__boundary,
        Third_step,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[7];
    State currentState;
    State history[1];
    void save_history( State compositeState, State subState );
    bool check_history( State compositeState, State subState );
    void update_state( State newState );
    void entryaction_____First_step( const UMLRTMessage * msg );
    void entryaction_____Fourth_step( const UMLRTMessage * msg );
    void entryaction_____Second_step( const UMLRTMessage * msg );
    void entryaction_____Third_step( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____Second_step__new_transition_1_to_unvisited_boundary( const UMLRTMessage * msg );
    void actionchain_____Second_step__new_transition_2_to_visited_boundary( const UMLRTMessage * msg );
    void actionchain_____Second_step__new_transition_3( const UMLRTMessage * msg );
    void actionchain_____transition1( const UMLRTMessage * msg );
    void actionchain_____transition2( const UMLRTMessage * msg );
    void actionchain_____transition3( const UMLRTMessage * msg );
    void actionchain_____transition4( const UMLRTMessage * msg );
    State junction_____Second_step__connectionPoint1( const UMLRTMessage * msg );
    State choice_____Second_step__deephistory( const UMLRTMessage * msg );
    State state_____First_step( const UMLRTMessage * msg );
    State state_____Fourth_step( const UMLRTMessage * msg );
    State state_____Second_step__boundary( const UMLRTMessage * msg );
    State state_____Third_step( const UMLRTMessage * msg );
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
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    uint32_t DELAY;
};
extern const UMLRTCapsuleClass MotorController;

#endif

