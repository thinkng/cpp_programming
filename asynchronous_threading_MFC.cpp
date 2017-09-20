// asynchronous threading

// from main thread, call, 

class A: public CWinthread
{
	//task A
};

class B: public CWinthread
{
	//task B
};


class C: public CWinthread
{
	//task C
};

void Init()
{
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	m_dwETCProcMask = (long long)0x01 << (siSysInfo.dwNumberOfProcessors - 3);
	//3 = Main thead  + 2 cores for the other 2 threads

	m_pA = (_A_Class_ *)AfxBeginThread(RUNTIME_CLASS(_A_Class_)); //Start thread A
	m_pA->SuspendThread(); //pause thread										
	m_pA->SetThreadPriority(THREAD_PRIORITY_IDLE);
	SetThreadAffinityMask(m_ppScanArea->m_hThread, m_dwETCProcMask); //set processing core to be reserved for this thread

	m_pB = (_B_Class_ *)AfxBeginThread(RUNTIME_CLASS(_B_Class_)); //Start thread B
	m_pB->SuspendThread(); //pause thread										
	m_pB->SetThreadPriority(THREAD_PRIORITY_IDLE);
	SetThreadAffinityMask(m_ppScanArea->m_hThread, m_dwETCProcMask); //set processing core to be reserved for this thread

	m_pC = (_C_Class_ *)AfxBeginThread(RUNTIME_CLASS(_C_Class_)); //Start thread C
	m_pC->SuspendThread(); //pause thread										
	m_pC->SetThreadPriority(THREAD_PRIORITY_IDLE);
	SetThreadAffinityMask(m_ppScanArea->m_hThread, m_dwETCProcMask); //set processing core to be reserved for this thread
}

void TerminateThread(_thread_id_)	
{
	DWORD exit_code = NULL;
	switch _thread_id_:
	case A:
		GetExitCodeThread(m_pA->m_hThread, &exit_code);
		if (exit_code == STILL_ACTIVE)
		{
			::TerminateThread(m_pA->m_hThread, 0);
			CloseHandle(m_pA->m_hThread);
		}
		m_pA->m_hThread = NULL;		
		break;
	case B:	
		GetExitCodeThread(m_pB->m_hThread, &exit_code);
		if (exit_code == STILL_ACTIVE)
		{
			::TerminateThread(m_pB->m_hThread, 0);
			CloseHandle(m_pB->m_hThread);
		}
		m_pB->m_hThread = NULL;	
        break;
    case C:
    	GetExitCodeThread(m_pC->m_hThread, &exit_code);
		if (exit_code == STILL_ACTIVE)
		{
			::TerminateThread(m_pC->m_hThread, 0);
			CloseHandle(m_pC->m_hThread);
		}
		m_pC->m_hThread = NULL;	
}

void main()
{
	_A_Class_* m_pA = new _A_Class_();
	_B_Class_* m_pB = new _B_Class_();
	_C_Class_* m_pC = new _C_Class_();

	Init();

	_GlobalEvent = _GlobalEvent_Querry_;

	while(_GlobalEvent == RUN)
	{
		_EventID = _get_event_method_;
		switch _EventID:
		case _start_A:
			m_pA->ResumeThread();
			break;
		case _start_B:
			m_pA->ResumeThread();
			break;
		case _start_C:
			m_pA->ResumeThread();
			break;
		case _pause_A:
			m_pA->SuspendThread();
			break;
		case _pause_B:
			m_pB->SuspendThread();
			break;
		case _pause_C:
			m_pC->SuspendThread();
			break;
		case _stop_all:
			TerminateThread(_thread_id_A);
			TerminateThread(_thread_id_A);
			TerminateThread(_thread_id_A);
			break;
	}

	delete m_pA;
	delete m_pB;
	delete m_pC;
}

	

