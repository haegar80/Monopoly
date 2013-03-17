#ifndef GameEngineClient_H
#define GameEngineClient_H

[event_source(native)]
class GameEngineClient {
public:
	__declspec(dllexport) GameEngineClient();
	__declspec(dllexport) virtual ~GameEngineClient();

	__declspec(dllexport) void DoSomething();

	__event void MyEvent();

};
#endif // GameEngineClient_H
