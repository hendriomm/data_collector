
#ifndef ENGINE_HH
#define ENGINE_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Engine
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal stopping() const;
        UMLRTOutSignal moveDownwards() const;
        UMLRTOutSignal moveUpwards() const;
        UMLRTOutSignal stopped() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal stopping() const;
        UMLRTInSignal moveDownwards() const;
        UMLRTInSignal moveUpwards() const;
        UMLRTInSignal stopped() const;
    };
    enum SignalId
    {
        signal_stopping = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_moveDownwards,
        signal_moveUpwards,
        signal_stopped
    };
};

#endif

