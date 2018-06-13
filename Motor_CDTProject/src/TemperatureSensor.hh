
#ifndef TEMPERATURESENSOR_HH
#define TEMPERATURESENSOR_HH

#include "Sensoring.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_TemperatureSensor : public UMLRTCapsule
{
public:
    Capsule_TemperatureSensor( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    UMLRTLogProtocol_baserole log;
    Sensoring::Conj sensoring;
public:
    enum BorderPortId
    {
        borderport_sensoring
    };
protected:
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
        DETECTING,
        IDLE,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[4];
    State currentState;
    void update_state( State newState );
    void entryaction_____IDLE( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____detecting( const UMLRTMessage * msg );
    void transitionaction_____transition1( const UMLRTMessage * msg );
    void transitionaction_____transition2( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____detecting( const UMLRTMessage * msg );
    void actionchain_____transition1( const UMLRTMessage * msg );
    void actionchain_____transition2( const UMLRTMessage * msg );
    State state_____DETECTING( const UMLRTMessage * msg );
    State state_____IDLE( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass TemperatureSensor;

#endif

