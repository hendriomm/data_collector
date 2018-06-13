
#include "Sensoring.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_sendData[] = 
{
    {
        "data",
        &UMLRTType_double,
        0,
        1,
        0
    }
};

static UMLRTObject payload_sendData = 
{
    sizeof( double ),
    1,
    fields_sendData
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

static UMLRTObject_field fields_startSensor[] = 
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

static UMLRTObject payload_startSensor = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_startSensor
};

static UMLRTObject_field fields_stopSensor[] = 
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

static UMLRTObject payload_stopSensor = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_stopSensor
};

Sensoring::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal Sensoring::Base::sendData() const
{
    UMLRTInSignal signal;
    signal.initialize( "sendData", signal_sendData, srcPort, &payload_sendData );
    return signal;
}

UMLRTInSignal Sensoring::Base::stopped() const
{
    UMLRTInSignal signal;
    signal.initialize( "stopped", signal_stopped, srcPort, &payload_stopped );
    return signal;
}

UMLRTOutSignal Sensoring::Base::startSensor() const
{
    UMLRTOutSignal signal;
    signal.initialize( "startSensor", signal_startSensor, srcPort, &payload_startSensor );
    return signal;
}

UMLRTOutSignal Sensoring::Base::stopSensor() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stopSensor", signal_stopSensor, srcPort, &payload_stopSensor );
    return signal;
}

Sensoring::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal Sensoring::Conj::sendData( double data ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "sendData", signal_sendData, srcPort, &payload_sendData, &data );
    return signal;
}

UMLRTOutSignal Sensoring::Conj::stopped() const
{
    UMLRTOutSignal signal;
    signal.initialize( "stopped", signal_stopped, srcPort, &payload_stopped );
    return signal;
}

UMLRTInSignal Sensoring::Conj::startSensor() const
{
    UMLRTInSignal signal;
    signal.initialize( "startSensor", signal_startSensor, srcPort, &payload_startSensor );
    return signal;
}

UMLRTInSignal Sensoring::Conj::stopSensor() const
{
    UMLRTInSignal signal;
    signal.initialize( "stopSensor", signal_stopSensor, srcPort, &payload_stopSensor );
    return signal;
}


