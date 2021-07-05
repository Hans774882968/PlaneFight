// PlaneFight.cpp : 整个项目的入口。

#include "framework.h"
#include "PlaneFight.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
GameState *gs;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void CALLBACK       moveBg(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
void                enemiesMove();
void                enemiesOutBound();
void                enemiesHitMyBullets();
void                enemiesHitMe();
void                enemyBulletsOutBound();
void                enemyBulletsHitMe();
void                meAnime();
void                myBulletsMove();
void                myBulletsOutBound();
void                myBulletsHitEnemyBullets();
void                myBulletsAnime();
void                enemyBulletsMove();
void                explosionUpdate();
void                bloodsMove();
void                bloodsHitMe();
void                bloodsGen();
void                updateCD();
void                changePassNum();//下一关
void CALLBACK       updateFlyObjects(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
void CALLBACK       enemiesGen(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
void CALLBACK       enemiesShoot(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
void                updateScreen(HDC hdc);//性能开销大，enemiesGen等函数仅等待updateFlyObjects调用。
void                shootMyBullets();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PLANEFIGHT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    
    srand((unsigned)time(NULL));
    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PLANEFIGHT));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLANEFIGHT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PLANEFIGHT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDC_PLANEFIGHT));//small icon把IDI_SMALL改成自定义图标

    return RegisterClassExW(&wcex);
}

void CALLBACK moveBg(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
    if (nIDEvent != 3) return;
    gs->moveBg();
    updateScreen(gs->hdc);
}

void CALLBACK updateFlyObjects(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
    if (nIDEvent != 1) return;
    changePassNum();//是否需要进入下一关
    enemiesMove();
    enemiesOutBound();
    enemiesHitMyBullets();
    enemiesHitMe();
    enemyBulletsOutBound();
    enemyBulletsHitMe();
    meAnime();
    myBulletsMove();
    myBulletsOutBound();
    myBulletsHitEnemyBullets();
    myBulletsAnime();
    enemyBulletsMove();
    explosionUpdate();
    bloodsMove();
    bloodsHitMe();
    bloodsGen();
    updateCD();
    updateScreen(gs->hdc);
}

void enemiesMove() {
    for (auto &enemy : gs->enemies) {
        enemy.move();
    }
}

void enemiesOutBound() {
    for (auto it = gs->enemies.begin(); it < gs->enemies.end();) {
        if (it->outBound()) {
            it = gs->enemies.erase(it);
        }
        else ++it;
    }
}

void enemiesHitMyBullets() {
    for (auto it = gs->enemies.begin(); it < gs->enemies.end();) {
        bool hit = false; int attack = 0;
        for (auto bul = gs->myBullets.begin(); bul < gs->myBullets.end(); ++bul) {
            if (it->collision(&*bul)) {
                hit = true;
                attack = bul->getAttack();
                gs->myBullets.erase(bul);
                break;
            }
        }
        if (hit) {
            bool died = it->decLife(attack);
            gs->explos.push_back(Explosion(it->x, it->y, gs->hdc));//爆炸特效
            PlaySound(_T("sound\\explosion.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
            if (died) {
                it = gs->enemies.erase(it);
                gs->sb.addScore(100);
            }
        }
        else ++it;
    }
}

void enemiesHitMe() {
    for (auto it = gs->enemies.begin(); it < gs->enemies.end();) {
        if (it->collision(gs->me)) {
            gs->explos.push_back(Explosion(it->x, it->y, gs->hdc));//爆炸特效
            PlaySound(_T("sound\\explosion.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
            it = gs->enemies.erase(it);
            bool died = gs->me->decLife();
        }
        else ++it;
    }
}

void enemyBulletsOutBound() {
    for (auto it = gs->enemyBullets.begin(); it < gs->enemyBullets.end();) {
        if (it->outBound()) {
            it = gs->enemyBullets.erase(it);
        }
        else ++it;
    }
}

void enemyBulletsHitMe() {
    for (auto it = gs->enemyBullets.begin(); it < gs->enemyBullets.end();) {
        if (it->collision(gs->me)) {
            it = gs->enemyBullets.erase(it);
            gs->explos.push_back(Explosion(gs->me->x, gs->me->y, gs->hdc));//爆炸特效
            PlaySound(_T("sound\\explosion.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
            bool died = gs->me->decLife();
        }
        else ++it;
    }
}

void meAnime() {
    if (!gs->me->isLevelUp) return;
    gs->me->anime();
}

void myBulletsMove() {
    for (auto& myBullet : gs->myBullets) {
        myBullet.move();
    }
}

void myBulletsOutBound() {
    for (auto it = gs->myBullets.begin(); it < gs->myBullets.end();) {
        if (it->outBound()) {
            it = gs->myBullets.erase(it);
        }
        else ++it;
    }
}

void myBulletsHitEnemyBullets() {
    for (auto mb = gs->myBullets.begin(); mb < gs->myBullets.end();) {
        bool hit = false;
        for (auto ene = gs->enemyBullets.begin(); ene < gs->enemyBullets.end(); ++ene) {
            if (mb->collision(&*ene)) {
                hit = true;
                gs->enemyBullets.erase(ene);
                break;
            }
        }
        if (hit) {
            gs->explos.push_back(Explosion(mb->x, mb->y, gs->hdc));//爆炸特效
            PlaySound(_T("sound\\explosion.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
            mb = gs->myBullets.erase(mb);
        }
        else ++mb;
    }
}

void myBulletsAnime() {
    for (auto &myBullet : gs->myBullets) {
        myBullet.anime();
    }
}

void enemyBulletsMove() {
    for (auto& enemyBullet : gs->enemyBullets) {
        enemyBullet.move();
    }
}

void CALLBACK enemiesShoot(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
    for (unsigned i = 0,j = 0; i < gs->enemies.size(); ++i) {
        if (!j) {
            j = rndInt(1, max(gs->enemies.size() / 5, 1));
            gs->enemies[i].shoot();
        }
        if (j > 0) --j;
    }
}

void CALLBACK enemiesGen(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
    if (gs->enemies.size() >= ENEMY_NUM) return;
    gs->enemies.push_back(Enemy(ENEMY_W, ENEMY_H, gs->sb.passNum, gs->hdc));
}

void explosionUpdate() {
    for (auto it = gs->explos.begin(); it < gs->explos.end();) {
        bool end = it->anime();
        if (end) it = gs->explos.erase(it);
        else ++it;
    }
}

void bloodsMove() {
    for (auto it = gs->bloods.begin(); it < gs->bloods.end();) {
        if (it->move()) {
            it = gs->bloods.erase(it);
        }
        else ++it;
    }
}

void bloodsHitMe() {
    for (auto it = gs->bloods.begin(); it < gs->bloods.end();) {
        if (it->collision(gs->me)) {
            it = gs->bloods.erase(it);
            gs->me->addBlood();
            PlaySound(_T("sound\\blood.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
        }
        else ++it;
    }
}

void bloodsGen() {
    if (!gs->sb.canGenerateBlood()) return;
    gs->bloods.push_back(Blood(BLOOD_W, BLOOD_H, gs->hdc));
}

void updateCD() {
    gs->levelUpCD.updateSkillCD();
    gs->protectCD.updateSkillCD();
    gs->silverBulletCD.updateSkillCD();
    if (gs->me->isLevelUp && gs->levelUpCD.getProcess() >= CD_TIME / 3) gs->me->levelDown();
    if (gs->me->isProtected && gs->protectCD.getProcess() >= CD_TIME / 3) gs->me->closeProtection();
}

void changePassNum() {//下一关
    if (!gs->sb.canFightBoss()) return;
    gs->sb.nextPass();
    gs->bgPrepare();
    gs->me->nextPass();
    gs->enemies.clear();
    gs->myBullets.clear();
    gs->enemyBullets.clear();
    gs->explos.clear();
    gs->bloods.clear();
    gs->levelUpCD = SkillCD();
    gs->protectCD = SkillCD();
    gs->silverBulletCD = SkillCD();
}

void drawBrush(COLORREF c,int lef,int top,int rig,int dwn) {
    HBRUSH bru = CreateSolidBrush(c);
    SelectObject(gs->hdc, bru);
    Rectangle(gs->hdc, lef, top, rig, dwn);
    DeleteObject(bru);
}

void updateScreen(HDC hdc) {
    gs->updateBg();
    gs->me->blit(gs->mdc, gs->bufdc);
    for (auto& enemy : gs->enemies) {
        enemy.blit(gs->mdc, gs->bufdc);
    }
    for (auto& myBullet : gs->myBullets) {
        myBullet.blit(gs->mdc, gs->bufdc);
    }
    for (auto& enemyBullet : gs->enemyBullets) {
        enemyBullet.blit(gs->mdc, gs->bufdc);
    }
    for (auto& explo : gs->explos) {
        explo.blit(gs->mdc, gs->bufdc);
    }
    for (auto& blood : gs->bloods) {
        blood.blit(gs->mdc, gs->bufdc);
    }
    StretchBlt(hdc, 0, 0, bgW, bgH, gs->mdc, 0, 0, bgW, bgH, SRCCOPY);
    WCHAR s[30];
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));//字体白色
    wsprintf(s, _T("当前关卡：%d"), gs->sb.passNum);
    TextOut(hdc, min(bgW / 2, 50), 50, s, _tcslen(s));
    wsprintf(s, _T("分数：%d"), gs->sb.score);
    TextOut(hdc, min(bgW / 2, 50), 70, s, _tcslen(s));
    wsprintf(s, _T("战机血量：%d"), gs->me->blood);
    TextOut(hdc, min(bgW / 2, 50), 90, s, _tcslen(s));
    wsprintf(s, _T("战机生命：%d"), gs->me->life);
    TextOut(hdc, min(bgW / 2, 50), 110, s, _tcslen(s));
    //提示可使用的技能
    if (gs->levelUpCD.canUseSkill()) {
        TextOut(hdc, min(bgW / 2, 50), bgH - 100, _T("按V战机可变身"), _tcslen(_T("按V战机可变身")));
    }
    if (gs->protectCD.canUseSkill()) {
        TextOut(hdc, min(bgW / 2, 50), bgH - 70, _T("按C可打开防护罩"), _tcslen(_T("按C可打开防护罩")));
    }
    if (gs->silverBulletCD.canUseSkill()) {
        TextOut(hdc, min(bgW / 2, 50), bgH - 40, _T("按X可使用战机大招"), _tcslen(_T("按X可使用战机大招")));
    }
    //血条、技能CD
    const int BRUSH_TXT_OFFSET = 70;
    drawBrush(RGB(255, 0, 0), bgW - 12 * MY_BLOOD, 35, bgW - 12 * (MY_BLOOD - gs->me->blood), 50);
    TextOut(hdc, bgW - 12 * MY_BLOOD - BRUSH_TXT_OFFSET, 35, _T("战机血量"), _tcslen(_T("战机血量")));
    wsprintf(s, _T("%d / %d"), gs->me->blood, MY_BLOOD);
    TextOut(hdc, bgW - 12 * MY_BLOOD + 12 * 4, 35, s, _tcslen(s));

    drawBrush(RGB(0, 0, 255), bgW - 4 * CD_TIME, 52, bgW - 4 * (CD_TIME - gs->levelUpCD.getProcess()), 67);
    TextOut(hdc, bgW - 4 * CD_TIME - BRUSH_TXT_OFFSET, 52, _T("变身冷却"), _tcslen(_T("变身冷却")));
    wsprintf(s, _T("%d / %d"), gs->levelUpCD.getProcess(), CD_TIME);
    TextOut(hdc, bgW - 4 * CD_TIME + 4 * 12, 52, s, _tcslen(s));

    drawBrush(RGB(0, 0, 255), bgW - 4 * CD_TIME, 69, bgW - 4 * (CD_TIME - gs->protectCD.getProcess()), 84);
    TextOut(hdc, bgW - 4 * CD_TIME - BRUSH_TXT_OFFSET, 69, _T("保护冷却"), _tcslen(_T("保护冷却")));
    wsprintf(s, _T("%d / %d"), gs->protectCD.getProcess(), CD_TIME);
    TextOut(hdc, bgW - 4 * CD_TIME + 4 * 12, 69, s, _tcslen(s));

    drawBrush(RGB(0, 0, 255), bgW - 4 * CD_TIME, 86, bgW - 4 * (CD_TIME - gs->silverBulletCD.getProcess()), 101);
    TextOut(hdc, bgW - 4 * CD_TIME - BRUSH_TXT_OFFSET, 86, _T("大招冷却"), _tcslen(_T("大招冷却")));
    wsprintf(s, _T("%d / %d"), gs->silverBulletCD.getProcess(), CD_TIME);
    TextOut(hdc, bgW - 4 * CD_TIME + 4 * 12, 86, s, _tcslen(s));
}

void shootMyBullets() {
    PlaySound(_T("sound\\bomb.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
    gs->myBullets.push_back(MyBullet(gs->me->x + gs->me->w / 2 - 30, gs->me->y - 15, gs->me->isLevelUp, gs->hdc));
    gs->myBullets.push_back(MyBullet(gs->me->x + gs->me->w / 2 + 10, gs->me->y - 15, gs->me->isLevelUp, gs->hdc));
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    MoveWindow(hWnd, 0, 0, 800, 700, true);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    mciSendString(L"open sound\\background.mp3 alias bgm", NULL, 0, NULL);
    mciSendString(L"play bgm repeat", NULL, 0, NULL);
    
    gs = new GameState(hWnd);
    
    SetTimer(hWnd, 1, FRAME_TIME, updateFlyObjects);
    SetTimer(hWnd, 2, 1500, enemiesShoot);
    SetTimer(hWnd, 3, 50, moveBg);
    SetTimer(hWnd, 4, 400, enemiesGen);
    updateScreen(gs->hdc);
    return TRUE;
}

void handle_keydown(WPARAM wParam) {
    gs->me->moveWithKeyBoard();
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000) {
        shootMyBullets();//发射子弹
    }
    if (wParam == 'X') {
        if (gs->silverBulletCD.canUseSkill()) {
            gs->sb.addScore(gs->sb.silverBulletGetScore(100));//加分
            for (const auto &enemy : gs->enemies) {
                gs->explos.push_back(Explosion(enemy.x, enemy.y, gs->hdc));//爆炸特效
            }
            gs->enemies.clear();//放大招
            PlaySound(_T("sound\\silver_bullet.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
            gs->silverBulletCD.useSkillCD();//更新CD
        }
    }
    else if (wParam == 'V') {
        if ((!gs->me->isLevelUp) && gs->levelUpCD.canUseSkill()) {
            gs->me->levelUp();//升级
            PlaySound(_T("sound\\level_up.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
            gs->levelUpCD.useSkillCD();
        }
    }
    else if (wParam == 'C') {
        if (gs->protectCD.canUseSkill()) {
            gs->me->openProtection();//保护
            PlaySound(_T("sound\\protect.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
            gs->protectCD.useSkillCD();
        }
    }
    //为了支持组合键而注释掉下面代码
    /*else if (wParam == VK_SPACE) {
        shootMyBullets();
    }
    else {
        bool moved = gs->me->moveWithKeyBoard(wParam);
        if (moved) enemiesHitMe();
    }*/
    //在此并不重绘屏幕，减少性能开销
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_KEYDOWN:
            handle_keydown(wParam);
            break;
        /*case WM_TIMER:
            break;*/
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                // 分析菜单选择:
                switch (wmId)
                {
                    case IDM_ABOUT:
                        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                        break;
                    case IDM_EXIT:
                        DestroyWindow(hWnd);
                        break;
                    default:
                        return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                if (gs != NULL) {
                    GetClientRect(hWnd, &(gs->rect));//自适应窗口大小
                    resizeDC(hdc, gs->mdc, gs->rect.Width(), gs->rect.Height());
                    updateScreen(hdc);
                }
                EndPaint(hWnd, &ps);
            }
            break;
        case WM_DESTROY:
            DeleteDC(gs->bufdc);
            DeleteDC(gs->mdc);
            ReleaseDC(hWnd, gs->hdc);
            KillTimer(hWnd, 1);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}