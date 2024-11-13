#include "register_types.hpp"
#include "SimulatorCanvas.hpp"

void initialize_fssimulator(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
    
    ClassDB::register_class<SimulatorCanvas>();
}

void uninitialize_fssimulator(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

extern "C" {
    // Initialization.
    GDExtensionBool GDE_EXPORT fssimulator_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_fssimulator);
        init_obj.register_terminator(uninitialize_fssimulator);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}