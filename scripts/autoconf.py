import kconfiglib
import sys

try:
    conf = kconfiglib.Kconfig("Kconfig")
    print(conf.load_config("prj.conf"))

    print(conf.write_autoconf("include/autoconf.h"))
except Exception as e:
    print("Critical Error: ", str(e))
    sys.exit(1)
