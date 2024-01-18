#include <iostream>
using namespace std;


class CDDrive
{
public:
	void Start()
	{
		cout << "CD Drive\nStart\n";
	}
	void CheckDisk()
	{
		cout << "Disk presence check\n";
	}
	void Stop()
	{
		cout << "Return to original position\n";
	}
};

class RAM
{
public:
	void StartDevices()
	{
		cout << "Launching devices\n";
	}
	void MemoryAnalyze()
	{
		cout << "Memory analysis\n";
	}
	void MemoryClear()
	{
		cout << "Memory clearn";
	}
};

class HDD
{
public:
	void Start()
	{
		cout << "Start (HDD)\n";
	}
	void BootSectorCheck() 
	{
		cout << "Boot sector check\n";
	}
	void Stop() 
	{
		cout << "Stop\n";
	}

};
class Videocard 
{
public:
	void Start() 
	{
		cout << "Launching the video card\n";
	}
	void MonitorCommunication() 
	{
		cout << "Checking connection with the monitor\n";
	}
	void DataOutput(RAM ram)
	{
		cout << "Displaying data about RAM\n";
	}
	void DataOutput(CDDrive cd_drive) 
	{
		cout << "Display information about the disk reader\n";
	}
	void DataOutput(HDD hdd) 
	{
		cout << "Displaying data about the hard drive\n";
	}

	void ShowMessage()
	{
		cout << "Display a farewell message on the monitor\n";
	}
};

class Power_Unit
{
public:
	void Energize()
	{
		cout << "Provide power to RAM\n";
	}
	void Energize(Videocard videocard)
	{
		cout << "Provide power to video card \n";
	}
	void Energize(RAM ram)
	{
		cout << "Provide power to RAM\n";
	}
	void Energize(CDDrive cd_drive)
	{
		cout << "Apply power to the disk reader\n";
	}
	void Energize(HDD hdd) 
	{
		cout << "Provide power to HDD\n";
	}
	void Deactivate(Videocard videocard)
	{
		cout << "Stop powering the video card\n";
	}
	void Deactivate(RAM ram)
	{
		cout << "Stop powering the RAM\n";
	}
	void Deactivate(CDDrive cd_drive)
	{
		cout << "Stop powering the disk reader\n";
	}
	void Deactivate(HDD hdd)
	{
		cout << "Stop powering the HDD\n";
	}
	void Deactivate()
	{
		cout << "OFF\n";
	}
};
class Sensors
{
public:
	void CheckVoltage()
	{
		cout << "Check voltage\n";
	}
	void Temperature(Power_Unit power_unit)
	{
		cout << "Check the temperature in the power supply\n";
	}
	void Temperature(Videocard videocard)
	{
		cout << "Check the temperature in the video card\n";
	}
	void Temperature(RAM ram)
	{
		cout << "Check the temperature in the RAM\n";
	}
	void CheckTemperatureAll() 
	{
		cout << "Check the temperature of all systems\n";
	}
};
class Facade
{
	Videocard videocard;
	RAM ram;
	HDD hdd;
	CDDrive cd_drive;
	Power_Unit powerUnit;
	Sensors sensors;
public:
	Facade(Videocard video, RAM ram, HDD hdd, CDDrive cd_drive, Power_Unit power, Sensors sensors)
	{
		videocard = video;
		this->ram = ram;
		powerUnit = power;
		sensors = sensors;
		this->hdd = hdd;
		this->cd_drive = cd_drive;
	}
	void Begin() 
	{
		powerUnit.Energize();
		sensors.CheckVoltage();
		sensors.Temperature(powerUnit);
		sensors.Temperature(videocard);
		powerUnit.Energize(videocard);
		videocard.Start();
		videocard.MonitorCommunication();
		sensors.Temperature(ram);
		powerUnit.Energize(ram);
		ram.StartDevices();
		ram.MemoryAnalyze();
		videocard.DataOutput(ram);
		powerUnit.Energize(cd_drive);
		cd_drive.Start();
		cd_drive.CheckDisk();
		videocard.DataOutput(cd_drive);
		powerUnit.Energize(hdd);
		hdd.Start();
		hdd.BootSectorCheck();
		videocard.DataOutput(hdd);
		sensors.CheckTemperatureAll();
	}
	void End()
	{
		hdd.Stop();
		ram.MemoryClear();
		ram.MemoryAnalyze();
		videocard.ShowMessage();
		cd_drive.Stop();
		powerUnit.Deactivate(videocard);
		powerUnit.Deactivate(ram);
		powerUnit.Deactivate(cd_drive);
		powerUnit.Deactivate(hdd);
		sensors.CheckVoltage();
		powerUnit.Deactivate();
	}
};

int main() 
{
	Videocard videocard;
	RAM ram;
	HDD hdd;
	CDDrive cdDrive;
	Power_Unit powerUnit;
	Sensors sensors;

	Facade facade(videocard, ram, hdd, cdDrive, powerUnit, sensors);
	facade.Begin();
	cout << endl << endl << endl;
	facade.End();

	return 0;
}