import os
import subprocess


def Generate():
    subprocess.run(["Vendor/premake/premake5.exe", "vs2022"])

def Delete():
    if (os.path.isfile("IntricateRecovery.sln")):
        os.remove("IntricateRecovery.sln")
        print("Deleted: IntricateRecovery.sln")

    if (os.path.isfile("IntricateRecovery/IntricateRecovery.vcxproj")):
        os.remove("IntricateRecovery/IntricateRecovery.vcxproj")
        print("Deleted: IntricateRecovery/IntricateRecovery.vcxproj")

    if (os.path.isfile("IntricateRecovery/IntricateRecovery.vcxproj.filters")):
        os.remove("IntricateRecovery/IntricateRecovery.vcxproj.filters")
        print("Deleted: IntricateRecovery/IntricateRecovery.vcxproj.filters")

    if (os.path.isfile("IntricateRecovery/IntricateRecovery.vcxproj.user")):
        os.remove("IntricateRecovery/IntricateRecovery.vcxproj.user")
        print("Deleted: IntricateRecovery/IntricateRecovery.vcxproj.user")


if __name__ == "__main__":
    os.chdir("../")
    Delete()
    print("\n")
    Generate()

    input("Press Enter to continue...")
