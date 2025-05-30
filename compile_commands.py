import json
import os
import re

project_root = os.path.abspath(os.path.dirname(__file__))
build_dir = os.path.join(project_root, "build")
src_dir = os.path.join(project_root, "src")

compile_commands = []

# Expressão regular pra capturar comandos de compilação
pattern = re.compile(r"g\+\+ .*? -c (\S+) -o (\S+)")

with os.popen("make clean && make -B") as pipe:
    for line in pipe:
        match = pattern.search(line)
        if match:
            source_file = os.path.abspath(match.group(1))
            output_file = os.path.abspath(match.group(2))
            command = line.strip()

            compile_commands.append({
                "directory": project_root,
                "command": command,
                "file": source_file
            })

with open("compile_commands.json", "w") as f:
    json.dump(compile_commands, f, indent=2)

print(f"✅ Gerado compile_commands.json com {len(compile_commands)} arquivos")
