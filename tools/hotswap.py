import sys
import os
import shutil
import websockets
import time
import asyncio
import winreg

"""
Script to hotswap plugin from bakkesmod process.

1. Connects to BakkesMod rcon
2. Unloads plugin
3. Replaces DLL file
4. Loads plugin
"""

registry_key = r'Software\BakkesMod\AppPath'
registry_value = "BakkesModPath"

bakkesmod_server = 'ws://127.0.0.1:9002'
rcon_password = 'password'


def get_bakkesmod_plugin_folder():
    bakkesmod_path = ""

    try:
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, registry_key)
        bakkesmod_path, type_id = winreg.QueryValueEx(key, registry_value)
    except OSError as e:
        print("Error while reading (HKEY_CURRENT_USER\\" + registry_key + ";" + registry_value + "):")
        print(str(e))
        sys.exit()

    print("Found BakkesModPath = " + bakkesmod_path)
    return bakkesmod_path + "plugins\\"


def replace_plugin_file():
    filename = os.path.basename(plugin_path)
    dst_path = get_bakkesmod_plugin_folder() + filename

    print("Swapping...")
    print(dst_path)
    print(plugin_path)

    if os.path.exists(dst_path):
        os.remove(dst_path)
    shutil.copyfile(plugin_path, dst_path)


async def hotswap():
    try:
        async with websockets.connect(bakkesmod_server, timeout=.1) as websocket:
            await websocket.send('rcon_password ' + rcon_password)
            auth_status = await websocket.recv()
            assert auth_status == 'authyes'

            filename = os.path.basename(plugin_path)
            plugin_name = filename[0:filename.index('.')]

            await websocket.send("plugin unload " + plugin_name)
            time.sleep(0.1)
            replace_plugin_file()
            time.sleep(0.1)
            await websocket.send("plugin load " + plugin_name)
    except:
        replace_plugin_file()


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print("Expected 1 argument, but received 0")
        print("Don't forget to pass the path to the compiled plugin.dll")
        sys.exit()

    print("Plugin path = " + sys.argv[1])
    plugin_path = sys.argv[1]
    asyncio.get_event_loop().run_until_complete(hotswap())
