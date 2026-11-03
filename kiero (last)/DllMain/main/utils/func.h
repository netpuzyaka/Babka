void panic_clean() {
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache\" /va /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU\" /va /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\FirstFolder\" /va /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRU\" /va /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\LastVisitedPidlMRULegacy\" /va /f");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\OpenSavePidlMRU\" /f");
    system("REG ADD \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ComDlg32\\OpenSavePidlMRU\"");
    system("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\" /f");
    system("REG ADD \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\"");
    system("REG DELETE \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\AppCompatCache\" /va /f");
    system("REG DELETE \"HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Session Manager\\AppCompatCache\" /va /f");
    system("REG DELETE \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\RADAR\\HeapLeakDetection\\DiagnosedApplications\" /f");
    system("REG ADD \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\RADAR\\HeapLeakDetection\\DiagnosedApplications\"");
    system("REG DELETE \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows\\CurrentVersion\\Search\\RecentApps\" /f");
    system("REG ADD \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows\\CurrentVersion\\Search\\RecentApps\"");
    system("REG DELETE \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\bam\\UserSettings\\%usersid%\" /va /f");
    system("REG DELETE \"HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\bam\\UserSettings\\%usersid%\" /va /f");
    system("REG DELETE \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store\" /va /f");
    system("REG DELETE  \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers\" /va /f");
    system("REG DELETE \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\" /f");
    system("REG ADD \"HKEY_USERS\\%usersid%\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2\"");

    system("DEL /f /q %APPDATA%\\Microsoft\\Windows\\Recent\\*.*");
    system("DEL /f /q %APPDATA%\\Microsoft\\Windows\\Recent\\CustomDestinations\\*.*");
    system("DEL /f /q %APPDATA%\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\*.*");
    system("DEL /f /q %systemroot%\\Panther\\*.*");
    system("DEL /f /q %systemroot%\\appcompat\\Programs\\*.txt");
    system("DEL /f /q %systemroot%\\appcompat\\Programs\\*.xml");
    system("DEL /f /q %systemroot%\\appcompat\\Programs\\Install\\*.txt");
    system("DEL /f /q %systemroot%\\appcompat\\Programs\\Install\\*.xml");
    system("DEL /f /q %systemroot%\\Prefetch\\*.pf");
    system("DEL /f /q %systemroot%\\Prefetch\\*.ini");
    system("DEL /f /q %systemroot%\\Prefetch\\*.7db");
    system("DEL /f /q %systemroot%\\Prefetch\\*.ebd");
    system("DEL /f /q %systemroot%\\Prefetch\\*.bin");
    system("DEL /f /q %systemroot%\\Prefetch\\*.db");
    system("DEL /f /q %systemroot%\\Prefetch\\ReadyBoot\\*.fx");
    system("DEL /f /q %systemroot%\\Minidump\\*.*");

    remove("C:\\kiero");
}
