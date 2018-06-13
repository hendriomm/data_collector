
#ifndef TOPCONTROLLERS_HH
#define TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Top,
    InstId_Top_controller,
    InstId_Top_motorDriver,
    InstId_Top_temperatureSensor
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Top_controller[];
extern UMLRTCommsPort internalports_Top_controller[];
extern UMLRTCommsPort borderports_Top_motorDriver[];
extern UMLRTCommsPort internalports_Top_motorDriver[];
extern UMLRTCommsPort borderports_Top_temperatureSensor[];
extern UMLRTCommsPort internalports_Top_temperatureSensor[];
extern UMLRTSlot Top_slots[];

#endif

