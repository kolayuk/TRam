
#ifndef TRAM_PAN_H
#define TRAM_PAN_H

/** TRam application panic codes */
enum TTRamPanics
	{
	ETRamUi = 1
	// add further panics here
	};

inline void Panic(TTRamPanics aReason)
	{
	_LIT(applicationName,"TRam");
	User::Panic(applicationName, aReason);
	}

#endif // TRAM_PAN_H
