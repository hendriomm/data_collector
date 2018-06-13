
#ifndef SENSORING_HH
#define SENSORING_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Sensoring
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal sendData() const;
        UMLRTInSignal stopped() const;
        UMLRTOutSignal startSensor() const;
        UMLRTOutSignal stopSensor() const;
    };
    enum SignalId
    {
        signal_sendData = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_stopped,
        signal_startSensor,
        signal_stopSensor
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal sendData( double data ) const;
        UMLRTOutSignal stopped() const;
        UMLRTInSignal startSensor() const;
        UMLRTInSignal stopSensor() const;
    };
};

#endif

