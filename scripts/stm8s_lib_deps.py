from helpers.find_deps import find_stm8s_includes_with_conditions, extract_define_targets
from helpers.generate_conf import generate_stm8s_conf_header

import pathlib
import subprocess

Import("env") # PIO env

# project foldder name and flag must be exactly the same!
project_name = str(env.GetProjectOption("build_src_flags")[0]).replace("-D ", "").lower()

src_path = pathlib.Path.cwd().joinpath("src")
codebase_path = src_path.joinpath("kernel")
program_path = src_path.joinpath("programs").joinpath(project_name)


if env.IsCleanTarget():
    # quick clean up
    subprocess.run("cd " + str(src_path) + " && rm stm8s_conf.h || true", shell=True, check=True, capture_output=True)
else:
    # find all important compile flags
    flags = extract_define_targets(str(program_path.joinpath("config.h")))

    # compile a list of all relevant stm8s based imports
    codebase_includes = find_stm8s_includes_with_conditions(str(codebase_path), flags)
    
    # check program file as well
    codebase_includes.extend(find_stm8s_includes_with_conditions(str(program_path)))

    # generate the stm8s_conf.h with those specified includes
    generate_stm8s_conf_header(str(src_path.joinpath("stm8s_conf.h")), codebase_includes)