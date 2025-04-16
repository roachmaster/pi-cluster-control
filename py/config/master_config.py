class MasterConfigDTO:
    def __init__(self, config: dict):
        self._config = config

    def get(self, key, default=None):
        return self._config.get(key, default)

    def get_modules(self):
        return self._config.get("MODULES", [])
    def get_templates(self):
        return self._config.get("TEMPLATES", {})
    def get_layouts(self):
        return self._config.get("LAYOUTS", {})
    def get_module_outputs(self):
        return self._config.get("MODULE_OUTPUTS", {})
    def get_generated_modules(self):
        return self._config.get("GENERATED_MODULES", [])
    def get_module_configs(self):
        return self._config.get("MODULE_CONFIGS", {})
    def get_module_config_list(self):
        return self._config.get("MODULE_CONFIG_LIST", [])

    def add_modules(self, item):
        self._config.setdefault("MODULES", []).append(item)
    def set_templates_entry(self, key, value):
        self._config.setdefault("TEMPLATES", {})[key] = value
    def set_layouts_entry(self, key, value):
        self._config.setdefault("LAYOUTS", {})[key] = value
    def set_module_outputs_entry(self, key, value):
        self._config.setdefault("MODULE_OUTPUTS", {})[key] = value
    def add_generated_modules(self, item):
        self._config.setdefault("GENERATED_MODULES", []).append(item)
    def set_module_configs_entry(self, key, value):
        self._config.setdefault("MODULE_CONFIGS", {})[key] = value
    def add_module_config_list(self, item):
        self._config.setdefault("MODULE_CONFIG_LIST", []).append(item)

    def raw(self):
        return self._config

    def __getitem__(self, key):
        return self._config[key]
    def has_module(self, name):
        return any(m.get("NAME") == name for m in self.get_modules())
    def find_module_by_name(self, name):
        return next((m for m in self.get_modules() if m.get("NAME") == name), None)
    def __setitem__(self, key, value):
        self._config[key] = value
