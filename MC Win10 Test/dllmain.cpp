#include "Utils.h"

class ClientInstance {
public:
    class Player* GetLocalPlayer() {
        static unsigned offset = 0;
        if (offset == NULL) {
            offset = *reinterpret_cast<int*>(Utils::FindSig("48 8B 89 ? ? ? ? 48 85 C9 ? ? 33 C0") + 3);
        }
        return *reinterpret_cast<Player**>((uintptr_t)(this) + offset);
    }
};

class Player {
public:
    virtual void Function0();
    virtual void Function1();
    virtual void Function2();
    virtual void Function3();
    virtual void Function4();
    virtual void Function5();
    virtual void Function6();
    virtual void Function7();
    virtual void remove(void);
    virtual void Function9();
    virtual void Function10();
    virtual void Function11();
    virtual void setPos(Vec3 const&);
};

Vec3* getVelOfEnt(Player* p) {
    static unsigned offset = 0;
    if (offset == NULL) {
        offset = *reinterpret_cast<int*>(Utils::FindSig("F3 0F 10 83 ? ? ? ? F3 0F ? ? ? F3 0F 10 8B ? ? ? ? F3 0F 11 ? ? F3 0F 10 83 ? ? ? ? F3 0F 11 ? ? 48 8B D7") + 3);
    }
    return reinterpret_cast<Vec3*>((uintptr_t)(p)+offset);
}

typedef void(__thiscall* CInstance)(ClientInstance*, void*);
CInstance _CInstance;

bool once = false;

void CInstance_Callback(ClientInstance* cInstance, void* a2) {
    if (!once) {
        Utils::DebugLogOutput("Hooked!");
        Player* player = cInstance->GetLocalPlayer();
        if (player != nullptr) {
            Vec3 tpPos = Vec3(0, 50, 0);
            player->setPos(tpPos);

            Vec3* vel = getVelOfEnt(player);
            vel->y += 2.0f;
        }
        once = true;
    }
    _CInstance(cInstance, a2);
}

void initDLL(LPVOID lpParam) {
    Utils::DeletePath("Client");

    uintptr_t cInstance_addr = Utils::FindSig("48 8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC 40 55");

    if (MH_Initialize() == MH_OK) { /* Only initialize once */
        if (MH_CreateHook((void*)cInstance_addr, &CInstance_Callback, reinterpret_cast<LPVOID*>(&_CInstance)) == MH_OK){
            MH_EnableHook((void*)cInstance_addr);
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)initDLL, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

