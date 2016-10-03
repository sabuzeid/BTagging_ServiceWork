static  const char* clnames[] = {
  "LCGReflex/PhysicsTools::MVATrainer",
  "LCGReflex/PhysicsTools::TreeTrainer",
};
extern "C" void SEAL_CAPABILITIES (const char**& names, int& n )
{names = clnames;n = sizeof(clnames)/sizeof(char*);}
