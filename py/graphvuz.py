from graphviz import Digraph
import graphviz

def build_forge_dag():
    dot = graphviz.Digraph("ForgeSystem", format="png")
    dot.attr(rankdir="TB", fontsize="10", fontname="Helvetica")
# === Nodes ===# Lambda DSL

    dot.attr("node", shape="box", style="filled", fillcolor="#e0f7fa")
    dot.node("LambdaBridge", "LambdaBridge\n(resolve, resolve_as)")

    # Provider Layer
    dot.attr("node", shape="box", style="filled", fillcolor="#e1bee7")
    dot.node("ForgeProvider", "ForgeProvider\n(resolve)")

    # Cache Interfaces & Implementations
    dot.attr("node", shape="box", style="filled", fillcolor="#f3e5f5")
    dot.node("LifecycleCache", "LifecycleCache\n(interface)", style="dashed")
    dot.node("SingletonCache", "SingletonCache")
    dot.node("ThreadLocalCache", "ThreadLocalCache")
    dot.node("SessionCache", "SessionCache")

    # Registry / Resolver
    dot.attr("node", shape="box", style="filled", fillcolor="#ffe0b2")
    dot.node("ForgeResolver", "ForgeResolver\n(resolve_forge)")
    dot.node("ForgeRegistry", "ForgeRegistry\n(get_forge)", style="dashed")
    dot.node("ForgeManager", "ForgeManager")

    # Forge and Forgeables
    dot.attr("node", shape="box", style="filled", fillcolor="#c8e6c9")
    dot.node("Forge", "Forge\n(interface)", style="dashed")
    dot.node("Forgeable", "Forgeable\n(interface)", style="dashed")
    dot.node("GoalValidate", "GoalValidate\n(execute)")

    # === Edges ===
    dot.edge("LambdaBridge", "ForgeProvider", label="delegates")
    dot.edge("ForgeProvider", "ForgeResolver", label="resolve_forge")
    dot.edge("ForgeResolver", "ForgeRegistry", label="uses")
    dot.edge("ForgeRegistry", "ForgeManager", label="impl.")
    dot.edge("ForgeResolver", "Forge", label="returns")
    dot.edge("Forge", "Forgeable", label="creates")
    dot.edge("GoalValidate", "Forgeable", arrowhead="empty", label="implements")

    # Lifecycle cache relations
    dot.edge("ForgeProvider", "LifecycleCache", label="selects")
    dot.edge("LifecycleCache", "SingletonCache")
    dot.edge("LifecycleCache", "ThreadLocalCache")
    dot.edge("LifecycleCache", "SessionCache")

    # Optional: LifecycleCache is a Forgeable
    dot.edge("LifecycleCache", "Forgeable", style="dashed", label="optional")


    return dot

def main():
    dag = build_forge_dag()
    dag.render('forge_dag', format='pdf', view=True)  # Generates and opens PDF

if __name__ == "__main__":
    main()