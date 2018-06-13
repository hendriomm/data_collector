
#include "Engine.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_stopping[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_stopping = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_stopping
};

static UMLRTObject_field fields_moveDownwards[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_moveDownwards = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_moveDownwards
};

static UMLRTObject_field fields_moveUpwards[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_moveUpwards = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_moveUpwards
};

static UMLRTObject_field fields_stopped[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_stopped = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_stopped
};

Engine::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal Engine::Base::stopping() const
{
    UMLRTInSignal signal;
    signal.initialize( "stopping", signal_stopping, srcPort, &payload_stopping );
    return signal;
}

UMLRTOutSignal Engine::Base::moveDownwards() const
{
    UMLRTOutSignal signal;
    signal.initialize( "moveDownwards", signal_moveDownwards, srcPort, &payload_moveDownwards );
    return signal;
}

UMLRTOutSignal Engine::Base::moveUpwards() const
{
    UMLRTOutSignal signal;
    signal.initialize( "moveUpwards", signal_moveUpwards, srcPort, &payload_moveUpwards );
    return signal;
}

UMLRTOutSignal Engine::Base::stopped() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stopped", signal_stopped, srcPort, &payload_stopped );
    return signal;
}

Engine::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Engine::Conj::stopping() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stopping", signal_stopping, srcPort, &payload_stopping );
    return signal;
}

UMLRTInSignal Engine::Conj::moveDownwards() const
{
    UMLRTInSignal signal;
    signal.initialize( "moveDownwards", signal_moveDownwards, srcPort, &payload_moveDownwards );
    return signal;
}

UMLRTInSignal Engine::Conj::moveUpwards() const
{
    UMLRTInSignal signal;
    signal.initialize( "moveUpwards", signal_moveUpwards, srcPort, &payload_moveUpwards );
    return signal;
}

UMLRTInSignal Engine::Conj::stopped() const
{
    UMLRTInSignal signal;
    signal.initialize( "stopped", signal_stopped, srcPort, &payload_stopped );
    return signal;
}


