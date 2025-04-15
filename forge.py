from py.master_config_loader import load_master_config, persist_master_config
from py.scaffold_module import scaffold_module


def main():
    master_config = load_master_config()
    modules = master_config.get("MODULES", [])

    print(f"🔧 Starting Forge generation for {len(modules)} modules...")

    for module in modules:
        scaffold_module(module, master_config)

    print("\n✅ All modules processed.\n")
    persist_master_config(master_config)


if __name__ == "__main__":
    main()
