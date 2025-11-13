#ifdef A
- 每一个终端设备使用100个arp缓存 - 交换机多一点，使用10000个arp表项，实现ip与mac地址的映射 - 每次要求我们输入ip地址，如果相同，则。。。。不同，则。。。。。
#endif

#include <stdio.h>
#include <wchar.h>   // 必须包含宽字符处理头文件
#include <locale.h>  // 用于设置本地化编码，避免中文乱码
#include <windows.h> // Windows系统头文件
// #include "../include/main.h"
// 颜色与加粗效果宏定义（ANSI 转义序列）
#define RESET "\033[0m"          // 重置所有样式（必须配对使用）
#define BOLD "\033[1m"           // 加粗效果
#define RED "\033[31m"           // 红色文本
#define GREEN "\033[32m"         // 绿色文本
#define YELLOW "\033[33m"        // 黄色文本（新增）
#define BOLD_RED "\033[1;31m"    // 加粗红色
#define BOLD_GREEN "\033[1;32m"  // 加粗绿色
#define BOLD_YELLOW "\033[1;33m" // 加粗黄色（新增组合样式）
    // mac定义
    typedef struct mac_
{
    char mac1;
    char mac2;
    char mac3;
    char mac4;
    char mac5;
    char mac6;
    char mac7;
    char mac8;
    char mac9;
    char mac10;
    char mac11;
    char mac12;
} mac;

// ip定义
typedef struct ip_
{
    int ip1;
    int ip2;
    int ip3;
    int ip4;
} ip;

// arp表项
typedef struct arp_entry_
{
    ip device_ip;   // 设备ip
    mac device_mac; // 设备mac
} arp_entry;

// 终端设备表项
typedef struct device_arp_entry_array_
{
    arp_entry arp_tab[100];
    int flags[100]; // 避免指针分配，使用标志判重，简单
} device_arp_entry_array;

// 交换机表项
typedef struct switch_arp_entry_array_
{
    arp_entry arp_tab[10000];
    int flags[10000]; // 避免指针分配，使用标志判重，简单
} switch_arp_entry_array;

// 当前假设固定为10台设备，一台交换机，一个VLAN。
// 一台设备
typedef struct device_
{
    device_arp_entry_array device_arp_tab; // 设备arp表项
    ip device_ip;                          // 设备ip
    mac device_mac;                        // 设备mac

} device;

// 一台交换机
typedef struct switch__
{
    switch_arp_entry_array switch_device; // 将交换机抽象为arp表项了
} switch_;

// 一个VLAN
typedef struct VLAN_
{
    ip VLAN_IP;
    device devices[10]; // 10台终端
    switch_ switch_s;   // 一台交换机
} VLAN;

// 分配子网的工作放在了main中实现！

#ifdef draft
VLAN网段掩码随机生成，这里大小使用的是255 : 255 : 255 : 0

#endif
// 随机数
#include <stdlib.h>
#include <time.h>
    VLAN vlan;
void init_vlan(VLAN *vlan);
void print_ip(ip *ip_);
void print_vlan(VLAN *vlan);
void print_mac(mac *device_mac);
void print_device(device *device_);
void one_test(device *dev_src, device *dev_desc, VLAN *vlan);
void device_info_add_switch(device *dev_src, VLAN *vlan);
BOOL search_all_devices(device *dev_src, device *dev_desc, VLAN *vlan);
void src_ask_arp_info_to_switch(device *dev_src, device *dev_desc, VLAN *vlan);
void init_vlan(VLAN *vlan)
{
    for (int i = 0; i < 10000; i++)
    {
        vlan->switch_s.switch_device.flags[i] = 0;
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            vlan->devices[i].device_arp_tab.flags[j] = 0;
        }
    }
}
// 索引0-9：数字0-9，索引10-35：大写字母A-Z
char mac_char[36] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'};

static int device_total = 10;
void init_device(device *dev)
{
    dev->device_ip.ip1 = device_total + 1;
    dev->device_ip.ip2 = device_total + 1;
    dev->device_ip.ip3 = device_total + 1;
    dev->device_ip.ip4 = device_total + 1;
    // 循环给 mac1~mac12 赋值随机字符（0-9/A-Z）
    for (int i = 0; i < 12; i++)
    {
        // 按成员顺序赋值：i=0→mac1, i=1→mac2, ..., i=11→mac12
        switch (i)
        {
        case 0:
            dev->device_mac.mac1 = mac_char[rand() % 36];
            break;
        case 1:
            dev->device_mac.mac2 = mac_char[rand() % 36];
            break;
        case 2:
            dev->device_mac.mac3 = mac_char[rand() % 36];
            break;
        case 3:
            dev->device_mac.mac4 = mac_char[rand() % 36];
            break;
        case 4:
            dev->device_mac.mac5 = mac_char[rand() % 36];
            break;
        case 5:
            dev->device_mac.mac6 = mac_char[rand() % 36];
            break;
        case 6:
            dev->device_mac.mac7 = mac_char[rand() % 36];
            break;
        case 7:
            dev->device_mac.mac8 = mac_char[rand() % 36];
            break;
        case 8:
            dev->device_mac.mac9 = mac_char[rand() % 36];
            break;
        case 9:
            dev->device_mac.mac10 = mac_char[rand() % 36];
            break;
        case 10:
            dev->device_mac.mac11 = mac_char[rand() % 36];
            break;
        case 11:
            dev->device_mac.mac12 = mac_char[rand() % 36];
            break;
        }
    }
}
int main()
{
    init_vlan(&vlan);
    printf("%ls%ls%ls%ls", BOLD, RED, "ddddddddd", RESET);
    // 关键：用当前时间设置种子，确保每次运行随机序列不同
    srand((unsigned int)time(NULL));
    // 初始化VLAN前三个网段 xxx.xxx.xxx.0
    vlan.VLAN_IP.ip1 = rand() % 256;
    vlan.VLAN_IP.ip2 = rand() % 256;
    vlan.VLAN_IP.ip3 = rand() % 256;
    vlan.VLAN_IP.ip4 = 0;

    // 每台主机初始化,默认10台
    for (int i = 0; i < device_total; i++)
    {
        // 初始化mac
        vlan.devices[i].device_mac.mac1 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac2 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac3 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac4 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac5 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac6 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac7 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac8 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac9 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac10 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac11 = mac_char[rand() % 36];
        vlan.devices[i].device_mac.mac12 = mac_char[rand() % 36];
        // 初始化ip
        vlan.devices[i].device_ip.ip1 = vlan.VLAN_IP.ip1;
        vlan.devices[i].device_ip.ip2 = vlan.VLAN_IP.ip2;
        vlan.devices[i].device_ip.ip3 = vlan.VLAN_IP.ip3;
        vlan.devices[i].device_ip.ip4 = i + 1;
        // printf("DEVICE_%d:\n", i);
        // print_device(&vlan.devices[i]);
        // printf("\n\n");
    }
    print_vlan(&vlan);
    // 建立通信,通信11次,一定至少有一次重复，观察现象
    // 为了便于观察,简化版本,指定源主机为1,后续可以乱序进行,更加符合真实情况
    // 这里是一定能找到的
    printf("Now,let's test link\n\n");
    for (int i = 0; i < device_total + 1; i++)
    {
        // 源端固定，目的端随机，重复10次，所有现象都看得到！
        one_test(&vlan.devices[0], &vlan.devices[rand() % device_total], &vlan);
        // printf("=====================================================================\n\n");
        printf("》》》》》》》》》》》》》》》》》》》《《《《《《《《《《《《《《《《《《《\n\n");
    }
    // 这里一定不能找到,会报错！
    device dev;
    init_device(&dev);
    one_test(&vlan.devices[0], &dev, &vlan);
}

void print_mac(mac *mac_)
{
    // 假设 mac_ 结构体中有12个字符成员：mac1~mac12（对应12位MAC地址）
    printf("MAC:%ls%ls%c%c-%c%c-%c%c-%c%c-%c%c-%c%c%ls\n", BOLD, RED,
           mac_->mac1, mac_->mac2,  // 第1组（前2位）
           mac_->mac3, mac_->mac4,  // 第2组
           mac_->mac5, mac_->mac6,  // 第3组
           mac_->mac7, mac_->mac8,  // 第4组
           mac_->mac9, mac_->mac10, // 第5组
           mac_->mac11, mac_->mac12 // 第6组（后2位）
           ,
           RESET);
}
void print_ip(ip *ip_)
{
    printf("IP:%ls%ls%d.%d.%d.%d%ls\n", BOLD, RED, ip_->ip1, ip_->ip2, ip_->ip3, ip_->ip4, RESET);
}
void print_device(device *device_)
{

    // print_mac(&device_->device_mac);
    // print_ip(&device_->device_ip);
    printf("【MAC:%ls%ls%c%c-%c%c-%c%c-%c%c-%c%c-%c%c%ls ", BOLD, RED,
           device_->device_mac.mac1, device_->device_mac.mac2,  // 第1组（前2位）
           device_->device_mac.mac3, device_->device_mac.mac4,  // 第2组
           device_->device_mac.mac5, device_->device_mac.mac6,  // 第3组
           device_->device_mac.mac7, device_->device_mac.mac8,  // 第4组
           device_->device_mac.mac9, device_->device_mac.mac10, // 第5组
           device_->device_mac.mac11, device_->device_mac.mac12 // 第6组（后2位）
           ,
           RESET);
    printf("IP:%ls%ls%d.%d.%d.%d%ls】 ", BOLD, RED, device_->device_ip.ip1, device_->device_ip.ip2, device_->device_ip.ip3, device_->device_ip.ip4, RESET);
}
void print_vlan(VLAN *vlan)
{
    wprintf(L"%ls", L"VLAN subnet ");
    print_ip(&vlan->VLAN_IP);
    wprintf(L"%ls", L"mask:255.255.255.0\n");
    for (int i = 0; i < device_total; i++)
    {
        print_device(&vlan->devices[i]);
        printf("\n");
    }
    printf("\n");
}

void one_test(device *dev_src, device *dev_desc, VLAN *vlan)
{
    // 建立连接调试信息
    //  printf("SRC:");
    printf("%ls%ls%d.%d.%d.%d%ls", BOLD, RED, dev_src->device_ip.ip1, dev_src->device_ip.ip2, dev_src->device_ip.ip3, dev_src->device_ip.ip4, RESET);
    printf("======================>");
    // printf("DESC:");
    printf("%ls%ls%d.%d.%d.%d%ls\n", BOLD, RED, dev_desc->device_ip.ip1, dev_desc->device_ip.ip2, dev_desc->device_ip.ip3, dev_desc->device_ip.ip4, RESET);
    // 源端与交换机交互
    // if(dev_desc->device_ip.ip4>device_total){
    //     return;
    // }
    src_ask_arp_info_to_switch(dev_src, dev_desc, vlan);
}

// 设备的信息存入交换机
void device_info_add_switch(device *dev_src, VLAN *vlan)
{
    // 设备信息已经再交换机中了！退出
    if (vlan->switch_s.switch_device.flags[dev_src->device_ip.ip4])
    {
        return;
    }
    else
    {
        // 否则加入其中
        vlan->switch_s.switch_device.flags[dev_src->device_ip.ip4] = 1;
    }
    // 交换机接收源端arp请求信息--ip_src
    vlan->switch_s.switch_device.arp_tab[dev_src->device_ip.ip4].device_ip = dev_src->device_ip;
    // 交换机接收源端arp请求信息--mac_src
    vlan->switch_s.switch_device.arp_tab[dev_src->device_ip.ip4].device_mac = dev_src->device_mac;
    // print_device(dev_src);
    printf("Add arp info ");
    print_device(dev_src);
    printf(" into switch\n");
}

// 设备的信息存入另一台设备的arp中
void device_info_add_another_one(device *dev_src, device *dev_desc)
{
    // 设备信息已经在目标设备中了！
    if (dev_src->device_arp_tab.flags[dev_desc->device_ip.ip4])
    {

        printf("arp info ");
        print_device(dev_desc);
        printf(" have Already existed in devive:");
        print_device(dev_src);
        printf("\n");
        return;
    }
    else
    {
        // 否则加入其中
        dev_src->device_arp_tab.flags[dev_desc->device_ip.ip4] = 1;
    }
    // 存入ip_src
    dev_src->device_arp_tab.arp_tab[dev_desc->device_ip.ip4].device_ip = dev_desc->device_ip;
    // 存入--mac_src
    dev_src->device_arp_tab.arp_tab[dev_desc->device_ip.ip4].device_mac = dev_desc->device_mac;
    printf("Add arp info: ");
    print_device(dev_desc);
    printf("into ");
    print_device(dev_src);
    printf("\n");
}

// 比较两个IP是否完全相等：所有分段都相等才返回真
BOOL compare_ip(ip ip1_, ip ip2_)
{
    // 关键：用 == 比较，且需比较所有4个分段（ip1~ip4）
    if ((ip1_.ip1 == ip2_.ip1) &&
        (ip1_.ip2 == ip2_.ip2) &&
        (ip1_.ip3 == ip2_.ip3) &&
        (ip1_.ip4 == ip2_.ip4))
    {
        // printf("》》》》》》》》》》》》》》》》》》》《《《《《《《《《《《《《《《《《《《\n");
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// 交换机遍历全部机器
BOOL search_all_devices(device *dev_src, device *dev_desc, VLAN *vlan)
{
    for (int i = 0; i < device_total; i++)
    {
        if ((i + 1 == (dev_src)->device_ip.ip4))
        {
            continue;
        }
        if (compare_ip(dev_desc->device_ip, vlan->devices[i].device_ip))
        {
            // 将访问到的目的端信息存储在交换机中
            device_info_add_switch(&vlan->devices[i], vlan);
            // 同理，目标端中也要加入源端的arp信息
            device_info_add_another_one(dev_desc, dev_src);
            // 源端也加入目标端信息。。。。。省略在后面吧，，更清晰
            printf("%ls%ls%s%ls", BOLD, GREEN, "FIND DESC_DEV", RESET);
            // 找到了，打印
            print_device(&vlan->devices[i]);
            printf("\n");
            return TRUE;
        }
    }

    printf("%ls%ls%s%ls\n", BOLD, YELLOW, compare_ip(dev_desc->device_ip, dev_src->device_ip) ? "CAN'T VISIT OWN" : "NO DESC_DEV YET", RESET);
    return FALSE;
}

void src_ask_arp_info_to_switch(device *dev_src, device *dev_desc, VLAN *vlan)
{
    // 与交换机交互的第一性原理，就是自身的信息会存入交换机
    device_info_add_switch(dev_src, vlan);
    // 交换机遍历全部机器,如果找到,交换机还要反馈给源端，源端再将信息存入arp缓存中
    if (search_all_devices(dev_src, dev_desc, vlan))
    {
        device_info_add_another_one(dev_src, dev_desc);
    }
}
