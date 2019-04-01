//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// http://msdn.microsoft.com/en-us/library/windows/apps/ff729724.aspx
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Player.h"
#include "Corridor.h"
#include "StopWatch.h"
#include "Room.h"
#include "OBJ_Loader.h"
int PIndexAmmount;
/*
https://github.com/Pindrought/DirectX-11-Engine-VS2017/blob/Tutorial_18/DirectX%2011%20Engine%20VS2017/DirectX%2011%20Engine%20VS2017/Graphics/Graphics.cpp



*/
objl::Loader loader;
float Height, Width; // Height And Width Values for viewport
GameObject Camera; //Game Camera 
GameObject FocusObject;  //Object that Camera Focuses on
Boundaries StartBlock, EndBlock; // Start And End Block For Level generation
Player objPlayer; //the Player 
Corridor objLevel1Corridor[6]; //6 Corridors
Room objRoom; // 1 Room
bool setup = true; //Uses to set up levels
int CurrentFrameRate, FPS; //FPS is the frame rate per secons
float LevelTime; //Time Taken to complete a level
float TotalTargets; //Total Number OF Targets in game world
float TargetsLeft; //Number of targets left
float TargetsKilled;
float PercentageKilled;
double Timer;
double DeltaTime = 0; 
XMVECTOR Eye, At, Up;
Stopwatch Frametimer;
Stopwatch Leveltimer;
std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
std::unique_ptr<DirectX::SpriteFont> spriteFont;
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	Vector3 Pos;
	Vector2 Tex;
	Vector3 Normal;
	Vector4 color;

};
//Creates View Buffer
struct CBNeverChanges
{
	XMMATRIX mView;
};
//Creates Projection Buffer
struct CBChangeOnResize
{
	XMMATRIX mProjection;
};
//Creates Object Buffer
struct CBChangesEveryFrame
{
	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};
//Creates Lighting Buffer
struct CBLightingBuffer
{
	XMMATRIX Ignore;
	XMFLOAT3 globalAmbient;
	float E = 1;
	XMFLOAT3 lightColor;
	float E1 = 1;
	XMFLOAT3 lightPosition;
	float E2 = 1;
	XMFLOAT3 eyePosition;
	float E3 = 1;
	XMFLOAT3 Ke;  //Emissive reflectance
	float E4 = 1;
	XMFLOAT3 Ka;  // Ambient reflectance
	float E5 = 1;
	XMFLOAT3 Kd; //Diffuse reflectance
	float E6 = 1;
	XMFLOAT3 Ks; //Specular reflectance
	float E7 = 1;
	float shininess;
};
D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
D3D11_TEXTURE2D_DESC descDepth = {};
CBNeverChanges cbNeverChanges;
//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = nullptr;
HWND                                g_hWnd = nullptr;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device1*                      Device1 = nullptr;

ID3D11DeviceContext1*               DevCon1 = nullptr;

IDXGISwapChain1*                    swapChain1 = nullptr;

ID3D11VertexShader*                 g_pVertexShader = nullptr;
ID3D11PixelShader*                  g_pPixelShader = nullptr;
ID3D11InputLayout*                  g_pVertexLayout = nullptr;
ID3D11Buffer*                       g_pVertexBuffer = nullptr;
ID3D11Buffer* g_pDiscoveryBuffer = nullptr;
ID3D11Buffer*                       g_pIndexBuffer = nullptr;
ID3D11Buffer* g_pDiscoveryIndex = nullptr;
ID3D11Buffer*                       g_pCBNeverChanges = nullptr;
ID3D11Buffer*                       g_pCBChangeOnResize = nullptr;
ID3D11Buffer*                       g_pCBChangesEveryFrame = nullptr;
ID3D11Buffer*    g_pCBLightBuffer = nullptr;

ID3D11ShaderResourceView* BlankTexture;
ID3D11ShaderResourceView* BrickTexture;
ID3D11ShaderResourceView* MarbleTexture;
ID3D11ShaderResourceView* Wall1Texture;
ID3D11ShaderResourceView* Wall2Texture;
ID3D11ShaderResourceView* TurretTexture;
ID3D11ShaderResourceView* TargetTexture;
ID3D11ShaderResourceView* Wall3Texture;
ID3D11Device*                       Device = nullptr;
ID3D11DeviceContext*                DevCon = nullptr;
IDXGISwapChain*                     swapChain = nullptr;
ID3D11RenderTargetView*             RenderTargetView = nullptr;


ID3D11Texture2D*                    DepthStencilBuffer = nullptr;
ID3D11DepthStencilView*             depthStencelView = nullptr;
ID3D11DepthStencilState * depthStencilState;
ID3D11RasterizerState * rasterizerState;

ID3D11SamplerState*                 g_pSamplerLinear = nullptr;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                           g_vMeshColor(0.7f, 0.7f, 0.7f, 1);

SimpleVertex *  DiscoveryVertex = NULL;
WORD *								DiscIndices = NULL;



//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	srand(time(NULL));
	rand();
	rand();
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}
	Frametimer.Start();
	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//	WndProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, 1920, 1080 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 7",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &Device, &g_featureLevel, &DevCon);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, &Device, &g_featureLevel, &DevCon);
		}

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		hr = Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}
	if (FAILED(hr))
		return hr;

	// Create swap chain
	IDXGIFactory2* dxgiFactory2 = nullptr;
	hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
	if (dxgiFactory2)
	{
		// DirectX 11.1 or later
		hr = Device->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&Device1));
		if (SUCCEEDED(hr))
		{
			(void)DevCon->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&DevCon1));
		}

		DXGI_SWAP_CHAIN_DESC1 sd = {};
		sd.Width = width;
		sd.Height = height;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;

		hr = dxgiFactory2->CreateSwapChainForHwnd(Device, g_hWnd, &sd, nullptr, nullptr, &swapChain1);
		if (SUCCEEDED(hr))
		{
			hr = swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&swapChain));
		}

		dxgiFactory2->Release();
	}
	else
	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = g_hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		hr = dxgiFactory->CreateSwapChain(Device, &sd, &swapChain);
	}

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER);

	dxgiFactory->Release();

	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return hr;

	hr = Device->CreateRenderTargetView(pBackBuffer, nullptr, &RenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// Create depth stencil texture

	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = Device->CreateTexture2D(&descDepth, nullptr, &DepthStencilBuffer);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view

	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = Device->CreateDepthStencilView(DepthStencilBuffer, &descDSV, &depthStencelView);
	if (FAILED(hr))
		return hr;

	DevCon->OMSetRenderTargets(1, &RenderTargetView, depthStencelView);





	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	hr = Device->CreateDepthStencilState(&depthstencildesc, &depthStencilState);
	if (FAILED(hr))
	{
		return false;
	}

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DevCon->RSSetViewports(1, &vp);
	Height = vp.Height;
	Width = vp.Width;


	//Create Rasterizer State
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	hr = Device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);



	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
	hr = Device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = Device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Set the input layout
	DevCon->IASetInputLayout(g_pVertexLayout);

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = Device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;

	if (loader.LoadFile("Discovery.obj") == true)
	{
		//Create Vertex Buffer
		const int max = loader.LoadedVertices.size();
		DiscoveryVertex = new SimpleVertex[max];
		for (int i = 0; i < max; i++)
		{
			DiscoveryVertex[i].Pos = Vector3(loader.LoadedVertices[i].Position.X, loader.LoadedVertices[i].Position.Y, loader.LoadedVertices[i].Position.Z);
			DiscoveryVertex[i].Normal = Vector3(loader.LoadedVertices[i].Normal.X, loader.LoadedVertices[i].Normal.Y, loader.LoadedVertices[i].Normal.Z);
			DiscoveryVertex[i].Tex = Vector2(loader.LoadedVertices[i].TextureCoordinate.X, loader.LoadedVertices[i].TextureCoordinate.Y);
		}

		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * max;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = DiscoveryVertex;
		hr = Device->CreateBuffer(&bd, &InitData, &g_pDiscoveryBuffer);
		if (FAILED(hr))
			return hr;

		// Set vertex buffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		DevCon->IASetVertexBuffers(0, 1, &g_pDiscoveryBuffer,&stride, &offset);

		//Create Index Buffer 
		const int IMax = loader.LoadedIndices.size();
		DiscIndices = new WORD[IMax];
		for (int i = 0; i < IMax; i++)
		{
			DiscIndices[i] = loader.LoadedIndices[i];
		}
	
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * IMax;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = DiscIndices;
		hr = Device->CreateBuffer(&bd, &InitData, &g_pDiscoveryIndex);
		if (FAILED(hr))
			return hr;
		PIndexAmmount = IMax;
		DevCon->IASetIndexBuffer(g_pDiscoveryIndex, DXGI_FORMAT_R16_UINT, 0);
	}


	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f),  XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

		{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },
		{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },

		{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f) , XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f) , XMFLOAT3(-1.0f, 0.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },

		{ Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector2(0.0f, 1.0f) , XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f) , XMFLOAT3(1.0f, 0.0f, 0.0f) },

		{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f) , XMFLOAT3(0.0f, 0.0f, -1.0f) },
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },

		{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ Vector3(1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f) , XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
	};

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) *  24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = vertices;
	hr = Device->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
		return hr;
	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	DevCon->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	hr = Device->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
		return hr;

	// Set index buffer
	DevCon->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBNeverChanges);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = Device->CreateBuffer(&bd, nullptr, &g_pCBNeverChanges);
	if (FAILED(hr))
		return hr;
	bd.ByteWidth = sizeof(CBChangeOnResize);
	hr = Device->CreateBuffer(&bd, nullptr, &g_pCBChangeOnResize);
	if (FAILED(hr))
		return hr;
	bd.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = Device->CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBLightingBuffer);
	hr = Device->CreateBuffer(&bd, nullptr, &g_pCBLightBuffer);
	if (FAILED(hr))
		return hr;

	// Load the Textures
	hr = CreateDDSTextureFromFile(Device, L"Textures/DDS/BT.dds", nullptr, &BlankTexture);
	hr = CreateDDSTextureFromFile(Device, L"Textures/DDS/Brick.dds", nullptr, &BrickTexture);
	hr = CreateDDSTextureFromFile(Device, L"Textures/DDS/Marble.dds", nullptr, &MarbleTexture);
	hr = CreateDDSTextureFromFile(Device, L"Textures/DDS/Wall1.dds", nullptr, &Wall1Texture);
	hr = CreateDDSTextureFromFile(Device, L"Textures/DDS/Wall2.dds", nullptr, &Wall2Texture);
	hr = CreateDDSTextureFromFile(Device, L"Textures/DDS/Wall3.dds", nullptr, &Wall3Texture);
	hr = CreateDDSTextureFromFile(Device, L"Textures/DDS/Target.dds", nullptr, &TargetTexture);
	if (FAILED(hr))
		return hr;
	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = Device->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrices
	g_World = XMMatrixIdentity();


	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 1000.0f);

	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	DevCon->UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
	return S_OK;
}

//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (DevCon) DevCon->ClearState();
	if (BlankTexture) BlankTexture->Release();
	if (BrickTexture) BrickTexture->Release();
	if (MarbleTexture) MarbleTexture->Release();
	if (Wall1Texture) Wall1Texture->Release();
	if (Wall2Texture) Wall2Texture->Release();
	if (Wall3Texture) Wall3Texture->Release();
	if (TargetTexture) TargetTexture->Release();
	if (g_pSamplerLinear) g_pSamplerLinear->Release();
	if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
	if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
	if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
	if (g_pCBLightBuffer) g_pCBLightBuffer->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pIndexBuffer) g_pIndexBuffer->Release();
	if (g_pVertexLayout) g_pVertexLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShader) g_pPixelShader->Release();
	if (DepthStencilBuffer) DepthStencilBuffer->Release();
	if (depthStencelView) depthStencelView->Release();
	if (RenderTargetView) RenderTargetView->Release();
	if (swapChain1) swapChain1->Release();
	if (swapChain) swapChain->Release();
	if (DevCon1) DevCon1->Release();
	if (DevCon) DevCon->Release();
	if (Device1) Device1->Release();
	if (Device) Device->Release();
}
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
bool KeycodeQ, KeycodeE, KeycodeW, KeycodeS, KeycodeA, KeycodeD, KeycodeX, KeycodeSpace, KeycodeShift, KeycodeLControl, KeycodeLeft, KeycodeRight, KeycodeUp, KeycodeDown, KeycodePlus, KeycodeMinus, KeycodeF; //Creating Keycode Bools
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		break;
		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.

		/*CHECKING AGAINST WPARAM AND SETTING VALUES TO TRUE OR FALSE BASED ON KEYPRESSES*/
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 70:
			KeycodeF = true;
			wParam = 0;
			break;
		case 65:
			KeycodeA = true;
			wParam = 0;
			break;
		case 68:
			KeycodeD = true;
			wParam = 0;
			break;
		case 87:
			KeycodeW = true;
			wParam = 0;
			break;
		case 83:
			KeycodeS = true;
			wParam = 0;
			break;
		case VK_SHIFT:
			KeycodeShift = true;
			wParam = 0;
			break;
		case 17:
			KeycodeLControl = true;
			wParam = 0;
			break;
		case 81:
			KeycodeQ = true;
			wParam = 0;
			break;
		case 69:
			KeycodeE = true;
			wParam = 0;
			break;
		case 88:
			KeycodeX = true;
			wParam = 0;
			break;
		case 32:
			KeycodeSpace = true;
			wParam = 0;
			break;
		case 37:
			KeycodeLeft = true;
			wParam = 0;
			break;
		case 39:
			KeycodeRight = true;
			wParam = 0;
			break;
		case 38:
			KeycodeUp = true;
			wParam = 0;
			break;
		case 40:
			KeycodeDown = true;
			wParam = 0;
			break;
		case 187:
			KeycodePlus = true;
			wParam = 0;
			break;
		case 189:
			KeycodeMinus = true;
			wParam = 0;
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 70:
			KeycodeF = false;
			wParam = 0;
			break;
		case 65:
			KeycodeA = false;
			wParam = 0;
			break;
		case 68:
			KeycodeD = false;
			wParam = 0;
			break;
		case 87:
			KeycodeW = false;
			wParam = 0;
			break;
		case 83:
			KeycodeS = false;
			wParam = 0;
			break;
		case VK_SHIFT:
			KeycodeShift = false;
			wParam = 0;
			break;
		case 17:
			KeycodeLControl = false;
			wParam = 0;
			break;
		case 81:
			KeycodeQ = false;
			wParam = 0;
			break;
		case 69:
			KeycodeE = false;
			wParam = 0;
			break;
		case 88:
			KeycodeX = false;
			wParam = 0;
			break;
		case 32:
			KeycodeSpace = false;
			wParam = 0;
			break;
		case 37:
			KeycodeLeft = false;
			wParam = 0;
			break;
		case 39:
			KeycodeRight = false;
			wParam = 0;
			break;
		case 38:
			KeycodeUp = false;
			wParam = 0;
			break;
		case 40:
			KeycodeDown = false;
			wParam = 0;
			break;
		case 187:
			KeycodePlus = false;
			wParam = 0;
			break;
		case 189:
			KeycodeMinus = false;
			wParam = 0;
			break;
		}
		break;
	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}



	return 0;
}
void GameObject::Draw()
{

	//Set Camera view
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	//Create Matrices
	XMMATRIX DrawMatrice;
	XMMATRIX PositionMatrix;

	//Create Draw Buffer
	CBChangesEveryFrame DrawBuffer;

	//Create Light Buffer
	CBLightingBuffer LightBuffer;
	
	//Set Mesh Colours
	g_vMeshColor.x = 1;//Red;
	g_vMeshColor.y =  1;//Green;
	g_vMeshColor.z =  1;// Blue;

	//Set Position Matrix
	PositionMatrix = XMMatrixTranslation(Position.x,
		Position.y,
		Position.z);
	
	
	//Create Rotation Matrix
XMMATRIX RotationMatrix;
	float X, Y, Z;
	X = Rotation.x;
	Y = Rotation.y;
	Z = Rotation.z;
	RotationMatrix = Matrix::CreateFromYawPitchRoll(X, Y, Z);
	XMMATRIX ScaleMatrix = XMMatrixScaling(Scale.x,
		Scale.y,
		Scale.z);




//Create LightBuffer Paramters
	LightBuffer.Ignore = XMMatrixIdentity();
	LightBuffer.globalAmbient = XMFLOAT3(0, 0, 0);
	LightBuffer.lightColor = XMFLOAT3(0, 1, 0);
	LightBuffer.lightPosition = objPlayer.Position;
	 X = XMVectorGetX(Eye);
	 Y = XMVectorGetY(Eye);
	 Z = XMVectorGetZ(Eye);
	LightBuffer.eyePosition = XMFLOAT3(Red,Green,Blue);
	LightBuffer.Ke = XMFLOAT3(1, 1, 1);
	LightBuffer.Ka = XMFLOAT3(1, 1, 1);
	LightBuffer.Kd = XMFLOAT3(1, 1, 1);
	LightBuffer.Ks = XMFLOAT3(1, 1, 1);
	LightBuffer.shininess = 1;

	//Set Draw Matrice using TRS
	DrawMatrice = ScaleMatrix * RotationMatrix * PositionMatrix;

	//Set Draw Buffer mWorld
	DrawBuffer.mWorld = XMMatrixTranspose(DrawMatrice);

	//Set View (Camera)
	cbNeverChanges.mView = XMMatrixTranspose(g_View);

	//Updating Buffers
	DevCon->UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &DrawBuffer, 0, 0);
	DevCon->UpdateSubresource(g_pCBNeverChanges, 0, nullptr, &cbNeverChanges, 0, 0);
	DevCon->UpdateSubresource(g_pCBLightBuffer, 0, nullptr, &LightBuffer, 0, 0);

	//Set Vertex Shader
	DevCon->VSSetShader(g_pVertexShader, nullptr, 0);

	//Set Vertex Shader Buffers
	DevCon->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
	DevCon->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
	DevCon->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	DevCon->VSSetConstantBuffers(3, 1, &g_pCBLightBuffer);
	
	//Set Pixel Shader 
	DevCon->PSSetShader(g_pPixelShader, nullptr, 0);

	//Set Pixel Shader Constant Buffer
	DevCon->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);

	//Set Texture
	DevCon->PSSetShaderResources(0, 1, &DrawTexture);

	//Set Sampler
	DevCon->PSSetSamplers(0, 1, &g_pSamplerLinear);

	//Draw Cube
	DevCon->DrawIndexed(36, 0, 0);
}
void Player::Draw()
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	//Set Vertex Buffer
	DevCon->IASetVertexBuffers(0, 1, &g_pDiscoveryBuffer, &stride, &offset);

	//Set Index Buffer
	DevCon->IASetIndexBuffer(g_pDiscoveryIndex, DXGI_FORMAT_R16_UINT, 0);

	//Set Camera view
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	//Create Matrices
	XMMATRIX DrawMatrice;
	XMMATRIX PositionMatrix;

	//Create Draw Buffer
	CBChangesEveryFrame DrawBuffer;

	//Create Light Buffer
	CBLightingBuffer LightBuffer;

	//Set Mesh Colours
	g_vMeshColor.x = Red;
	g_vMeshColor.y = Green;
	g_vMeshColor.z = Blue;

	//Set Position Matrix
	PositionMatrix = XMMatrixTranslation(Position.x,
		Position.y,
		Position.z);


	//Create Rotation Matrix
	XMMATRIX RotationMatrix;
	float X, Y, Z;
	X =Deg2Rad( Rotation.x);
	Y = Deg2Rad(Rotation.y);
	Z = Deg2Rad(Rotation.z);
	RotationMatrix = Matrix::CreateFromYawPitchRoll(X, Y, Z);
	XMMATRIX ScaleMatrix = XMMatrixScaling(Scale.x,
		Scale.y,
		Scale.z);




	//Create LightBuffer Paramters
	LightBuffer.Ignore = XMMatrixIdentity();
	LightBuffer.globalAmbient = XMFLOAT3(0, 0, 0);
	LightBuffer.lightColor = XMFLOAT3(0, 1, 0);
	LightBuffer.lightPosition = objPlayer.Position;
	X = XMVectorGetX(Eye);
	Y = XMVectorGetY(Eye);
	Z = XMVectorGetZ(Eye);
	LightBuffer.eyePosition = XMFLOAT3(X, Y, Z);
	LightBuffer.Ke = XMFLOAT3(Red, Green, Blue);
	LightBuffer.Ka = XMFLOAT3(1, 1, 1);
	LightBuffer.Kd = XMFLOAT3(1, 1, 1);
	LightBuffer.Ks = XMFLOAT3(1, 1, 1);
	LightBuffer.shininess = 1;

	//Set Draw Matrice using TRS
	DrawMatrice = ScaleMatrix * RotationMatrix * PositionMatrix;

	//Set Draw Buffer mWorld
	DrawBuffer.mWorld = XMMatrixTranspose(DrawMatrice);

	//Set View (Camera)
	cbNeverChanges.mView = XMMatrixTranspose(g_View);

	//Updating Buffers
	DevCon->UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &DrawBuffer, 0, 0);
	DevCon->UpdateSubresource(g_pCBNeverChanges, 0, nullptr, &cbNeverChanges, 0, 0);
	DevCon->UpdateSubresource(g_pCBLightBuffer, 0, nullptr, &LightBuffer, 0, 0);

	//Set Vertex Shader
	DevCon->VSSetShader(g_pVertexShader, nullptr, 0);

	//Set Vertex Shader Buffers
	DevCon->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
	DevCon->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
	DevCon->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	DevCon->VSSetConstantBuffers(3, 1, &g_pCBLightBuffer);

	//Set Pixel Shader 
	DevCon->PSSetShader(g_pPixelShader, nullptr, 0);

	//Set Pixel Shader Constant Buffer
	DevCon->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);

	//Set Texture
	DevCon->PSSetShaderResources(0, 1, &DrawTexture);

	//Set Sampler
	DevCon->PSSetSamplers(0, 1, &g_pSamplerLinear);

	//Draw Cube
	DevCon->DrawIndexed(PIndexAmmount, 0, 0);
}
bool EndLevel = false;
void Level1()
{
	/*Keyboard checks*/
	
	//If W is being pressed set player.W to true
	if (KeycodeW == true)
	{
		objPlayer.W = true;
	}
	else if (KeycodeW == false)
	{
		objPlayer.W = false;
	}

	//If A is being pressed set player.A to true
	if (KeycodeA == true)
	{
		objPlayer.A = true;

	}
	else if (KeycodeA == false)
	{
		objPlayer.A = false;
	}
	
	//If S is being pressed set player.S to true
	if (KeycodeS == true)
	{
		objPlayer.S = true;
	}
	else if (KeycodeS == false)
	{
		objPlayer.S = false;
	}

	//If D is being pressed set player.D to true
	if (KeycodeD == true)
	{
		objPlayer.D = true;
	}
	else if (KeycodeD == false)
	{
		objPlayer.D = false;
	}

	//If UP is being pressed set player.UP to true
	if (KeycodeUp == true)
	{
		objPlayer.UP = true;
	}
	else if (KeycodeUp == false)
	{
		objPlayer.UP = false;
	}

	//If RIGHT is being pressed set player.RIGHT to true
	if (KeycodeRight == true)

	{
		objPlayer.RIGHT = true;
	}
	else if (KeycodeRight == false)
	{
		objPlayer.RIGHT = false;
	}

	//If DOWN is being pressed set player.DOWN to true
	if (KeycodeDown == true)

	{
		objPlayer.DOWN = true;
	}
	else if (KeycodeDown == false)
	{
		objPlayer.DOWN = false;
	}

	//If LEFT is being pressed set player.LEFT to true
	if (KeycodeLeft == true)

	{
		objPlayer.LEFT = true;
	}
	else if (KeycodeLeft == false)
	{
		objPlayer.LEFT = false;
	}


	//If PLUS is being pressed set player.PLUS to true
	if (KeycodePlus == true)
	{
		objPlayer.PLUS = true;
	}
	else
	{
		objPlayer.PLUS = false;
	}


	//If MINUS is being pressed set player.MINUS to true
	if (KeycodeMinus == true)
	{
		objPlayer.MINUS = true;
	}
	else
	{
		objPlayer.MINUS = false;
	}

	//If F is being pressed set player.F to true
	if (KeycodeF == true)
	{
		objPlayer.F = true;
	}
	else
	{
		objPlayer.F = false;
	}

	//If Q is being pressed set player.Q to true
	if (KeycodeQ == true)
	{
		objPlayer.Q = true;
	}
	else if (KeycodeQ == false)
	{
		objPlayer.Q = false;
	}

	//If E is being pressed set player.E to true
	if (KeycodeE == true)
	{
		objPlayer.E = true;
	}
	else if (KeycodeE == false)
	{
		objPlayer.E = false;
	}

	//If SPACE is being pressed set player.SPACE to true
	if (KeycodeSpace == true)
	{
		objPlayer.SPACE = true;
	}
	else if (KeycodeSpace == false)
	{
		objPlayer.SPACE = false;
	}


	//If SHIFT is being pressed set player.SHIFT to true
	if (KeycodeShift == true)
	{
		objPlayer.SHIFT = true;
	}
	else if (KeycodeShift == false) {
		objPlayer.SHIFT = false;
	}


	//If LControl is being pressed set player.CONTROL to true
	if (KeycodeLControl == true)
	{
		objPlayer.CONTROL = true;
	}
	else if (KeycodeLControl == false) {
		objPlayer.CONTROL = false;
	}

	//If X is being pressed set player.X to true
	if (KeycodeX == true)
	{
		objPlayer.X = true;
	}
	else if (KeycodeX == false)
	{
		objPlayer.X = false;
	}


	//Level Setup
	if (setup == true)
	{
		//Initialsing Start Block
		BoundariesInit Start;
		Start.Position = Vector3(0, 0, 0);
		Start.Rotation;
		Start.Scale;
		Start.colourR;
		Start.colourG;
		Start.colourB;
		Start.targetchance = 0;
		Start.turretchance = 0;
		Start.leftWall = true;
		Start.rightWall = true;
		Start.frontwall = false;
		Start.backwall = true;
		Start.roof = true;
		Start.floor = true;
		Start.DrawTexture = BlankTexture;
		Start.TurretTexture = TargetTexture;
		Start.TargetTexture = TargetTexture;
		StartBlock.Setup(Start);

		//Initialising Player
		playerInit player;
		player.Position = StartBlock.Position;
		player.Position.y += 5;
		player.Scale = Vector3(1, 1, 1);
		player.colourB = 1;
		player.colourG = 1;
		player.colourB = 1;
		player.Health = 100;
		player.Rotation = Vector3(0, 0, 0);
		player.Shots = 0;
		player.DrawTexture = BlankTexture;
		objPlayer.Setup(player);

		//Initialising Corridor 0
		corridorsInit Corridor1;
		Corridor1.Position = StartBlock.Position;
		Corridor1.Position.x += 10;
		Corridor1.Rotation;
		Corridor1.Scale;
		Corridor1.colourR;
		Corridor1.colourG;
		Corridor1.colourB;
		Corridor1.floorLength = rand() % 50 + 2;//Randomnises Corridor Length
		Corridor1.CorridorDirection = "Forward";
		Corridor1.DrawTexture = MarbleTexture;
		Corridor1.TurretTexture = TargetTexture;
		Corridor1.TargetTexture = TargetTexture;
		Corridor1.FirstBlock.leftWall = true;
		Corridor1.FirstBlock.rightWall = true;
		Corridor1.FirstBlock.frontwall = false;
		Corridor1.FirstBlock.backwall = false;
		Corridor1.FirstBlock.roof = true;
		Corridor1.FirstBlock.floor = true;
		Corridor1.LastBlock.leftWall = true;
		Corridor1.LastBlock.rightWall = true;
		Corridor1.LastBlock.frontwall = false;
		Corridor1.LastBlock.backwall = false;
		Corridor1.LastBlock.roof = true;
		Corridor1.LastBlock.floor = true;
		objLevel1Corridor[0].Setup(Corridor1);
		setup = false;



		//Initialising Corridor 1
		int Length = objLevel1Corridor[0].FloorLength;
		Corridor1.Position = objLevel1Corridor[0].objBoundaries[Length - 1].Position;
		Corridor1.Position.x += 10;
		Corridor1.Rotation;
		Corridor1.Scale;
		Corridor1.colourR;
		Corridor1.colourG;
		Corridor1.colourB;
		Corridor1.floorLength = rand() % 50 + 2;//Randomnises Corridor Length
		Corridor1.CorridorDirection = "Right";
		Corridor1.DrawTexture = Wall1Texture;
		Corridor1.TurretTexture = TargetTexture;
		Corridor1.TargetTexture = TargetTexture;
		Corridor1.FirstBlock.leftWall = true;
		Corridor1.FirstBlock.rightWall = false;
		Corridor1.FirstBlock.frontwall = true;
		Corridor1.FirstBlock.backwall = false;
		Corridor1.FirstBlock.roof = true;
		Corridor1.FirstBlock.floor = true;
		Corridor1.LastBlock.leftWall = false;
		Corridor1.LastBlock.rightWall = true;
		Corridor1.LastBlock.frontwall = true;
		Corridor1.LastBlock.backwall = true;
		Corridor1.LastBlock.roof = false;
		Corridor1.LastBlock.floor = true;
		objLevel1Corridor[1].Setup(Corridor1);


		//Initialising Corridor 2
		Length = objLevel1Corridor[1].FloorLength;
		Corridor1.Position = objLevel1Corridor[1].objBoundaries[Length - 1].Position;
		Corridor1.Position.x += 0;
		Corridor1.Rotation;
		Corridor1.Scale;
		Corridor1.colourR;
		Corridor1.colourG;
		Corridor1.colourB;
		Corridor1.floorLength = rand() % 50 + 2;//Randomnises Corridor Length
		Corridor1.CorridorDirection = "Up";
		Corridor1.DrawTexture = Wall2Texture;
		Corridor1.TurretTexture = TargetTexture;
		Corridor1.TargetTexture = TargetTexture;
		Corridor1.FirstBlock.leftWall = false;
		Corridor1.FirstBlock.rightWall = false;
		Corridor1.FirstBlock.frontwall = false;
		Corridor1.FirstBlock.backwall = false;
		Corridor1.FirstBlock.roof = false;
		Corridor1.FirstBlock.floor = false;
		Corridor1.LastBlock.leftWall = true;
		Corridor1.LastBlock.rightWall = true;
		Corridor1.LastBlock.frontwall = true;
		Corridor1.LastBlock.backwall = false;
		Corridor1.LastBlock.roof = true;
		Corridor1.LastBlock.floor = false;
		objLevel1Corridor[2].Setup(Corridor1);

		//Initialising Corridor 3
		Length = objLevel1Corridor[2].FloorLength;
		Corridor1.Position = objLevel1Corridor[2].objBoundaries[Length - 1].Position;
		Corridor1.Position.x -= 10;
		Corridor1.Rotation;
		Corridor1.Scale;
		Corridor1.colourR;
		Corridor1.colourG;
		Corridor1.colourB;
		Corridor1.floorLength = rand() % 50 + 2; //Randomnises Corridor Length
		Corridor1.CorridorDirection = "Backward";
		Corridor1.DrawTexture = Wall3Texture;
		Corridor1.TurretTexture = TargetTexture;
		Corridor1.TargetTexture = TargetTexture;
		Corridor1.FirstBlock.leftWall = true;
		Corridor1.FirstBlock.rightWall = true;
		Corridor1.FirstBlock.frontwall = false;
		Corridor1.FirstBlock.backwall = false;
		Corridor1.FirstBlock.roof = true;
		Corridor1.FirstBlock.floor = true;
		Corridor1.LastBlock.leftWall = true;
		Corridor1.LastBlock.rightWall = false;
		Corridor1.LastBlock.frontwall = false;
		Corridor1.LastBlock.backwall = true;
		Corridor1.LastBlock.roof = true;
		Corridor1.LastBlock.floor = true;
		objLevel1Corridor[3].Setup(Corridor1);



		roomInit Room1;
		Length = objLevel1Corridor[3].FloorLength;
		Room1.Position = objLevel1Corridor[3].objBoundaries[Length - 1].Position;
		Room1.Position.z += 10;
		Room1.Rotation;
		Room1.Scale;
		Room1.colourR;
		Room1.colourG;
		Room1.colourB;
		Room1.targetchance;
		Room1.turretchance;
		Room1.DrawTexture = MarbleTexture;
		Room1.TurretTexture = TargetTexture;
		Room1.TargetTexture = TargetTexture;
		objRoom.Setup(Room1);


		//Initialising Corridor 4
		Length = objLevel1Corridor[3].FloorLength;
		Corridor1.Position = objLevel1Corridor[3].objBoundaries[Length - 1].Position;
		Corridor1.Position.z -= 10;
		Corridor1.Rotation;
		Corridor1.Scale;
		Corridor1.colourR;
		Corridor1.colourG;
		Corridor1.colourB;
		Corridor1.floorLength = rand() % 50 + 2;//Randomnises Corridor Length
		Corridor1.CorridorDirection = "Right";
		Corridor1.DrawTexture = BrickTexture;
		Corridor1.TurretTexture = TargetTexture;
		Corridor1.TargetTexture = TargetTexture;
		Corridor1.FirstBlock.leftWall = false;
		Corridor1.FirstBlock.rightWall = false;
		Corridor1.FirstBlock.frontwall = true;
		Corridor1.FirstBlock.backwall = true;
		Corridor1.FirstBlock.roof = true;
		Corridor1.FirstBlock.floor = true;
		Corridor1.LastBlock.leftWall = false;
		Corridor1.LastBlock.rightWall = true;
		Corridor1.LastBlock.frontwall = true;
		Corridor1.LastBlock.backwall = true;
		Corridor1.LastBlock.roof = true;
		Corridor1.LastBlock.floor = false;
		objLevel1Corridor[4].Setup(Corridor1);



		//Initialising Corridor 5
		Length = objLevel1Corridor[4].FloorLength;
		Corridor1.Position = objLevel1Corridor[4].objBoundaries[Length - 1].Position;
		Corridor1.Position.y -= 10;
		Corridor1.Rotation;
		Corridor1.Scale;
		Corridor1.colourR;
		Corridor1.colourG;
		Corridor1.colourB;
		Corridor1.floorLength = rand() % 50 + 2; //Randomnises Corridor Length
		Corridor1.CorridorDirection = "Down";
		Corridor1.DrawTexture = MarbleTexture;
		Corridor1.TurretTexture = TargetTexture;
		Corridor1.TargetTexture = TargetTexture;
		Corridor1.FirstBlock.leftWall = true;
		Corridor1.FirstBlock.rightWall = true;
		Corridor1.FirstBlock.frontwall = true;
		Corridor1.FirstBlock.backwall = true;
		Corridor1.FirstBlock.roof = false;
		Corridor1.FirstBlock.floor = false;
		Corridor1.LastBlock.leftWall = true;
		Corridor1.LastBlock.rightWall = true;
		Corridor1.LastBlock.frontwall = true;
		Corridor1.LastBlock.backwall = true;
		Corridor1.LastBlock.roof = false;
		Corridor1.LastBlock.floor = false;
		objLevel1Corridor[5].Setup(Corridor1);


		//Creates End Block 
		BoundariesInit End;
		Length = objLevel1Corridor[5].FloorLength;
		End.Position = objLevel1Corridor[5].objBoundaries[Length - 1].Position;
		End.Position.y -= 10;
		End.Rotation;
		End.Scale;
		End.colourR = 0;
		End.colourG = 1;
		End.colourB = 0;
		End.targetchance = 0;
		End.turretchance = 0;
		End.leftWall = true;
		End.rightWall = true;
		End.frontwall = true;
		End.backwall = true;
		End.roof = false;
		End.floor = true;
		End.DrawTexture = BlankTexture;
		End.TurretTexture = TargetTexture;
		End.TargetTexture = TargetTexture;
		EndBlock.Setup(End);
		Leveltimer.Restart();
		Leveltimer.Start();
		TotalTargets = 0;
		//Checks how many targets are alive in game world at start up
		for (int c = 0; c < 6; c++)
		{
			for (int F = 0; F < objLevel1Corridor[c].FloorLength; F++)
			{

				//If taget is alive add one to total targets
				if (objLevel1Corridor[c].objBoundaries[F].TARGET == true)
				{

					//Adds one to total Targets
					TotalTargets++;
				}
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (objRoom.ObjBoundaries[i].TARGET == true)
			{
				TotalTargets++;
			}
		}
		if (objRoom.Entrance.TARGET == true)
		{
			TotalTargets++;
		}
	}


	//Resets Targets LEeft
	TargetsLeft = 0;

	//Checks how many targets alive in game world
	for (int c = 0; c < 6; c++)
	{
		for (int F = 0; F < objLevel1Corridor[c].FloorLength; F++)
		{
			//if the targets is alive add one to targets left
			if (objLevel1Corridor[c].objBoundaries[F].TARGET == true)
			{
				//Adding one to targets left
				TargetsLeft++;
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (objRoom.ObjBoundaries[i].TARGET == true)
		{
			TargetsLeft++;
		}
	}
	if (objRoom.Entrance.TARGET == true)
	{
		TargetsLeft++;
	}

	////Bullets VS Targets Room Collision Checks
	//for (int B = 0; B < 50; B++)
	//{
	//	for (int i = 0; i < 100; i++)
	//	{

	//		//Checking for Gun Left
	//		if (objPlayer.objGunLeft.objbulletlist[B].Alive == true)
	//		{
	//			for (int F = 0; F < 100; F++)
	//			{

	//				//Checking Target is alive
	//				if (objRoom.ObjBoundaries[F].objTarget.Health >= 0)
	//				{

	//					//Checking for colliision	
	//					if (CollisionBox::Intersects(objPlayer.objGunLeft.objbulletlist[B], objRoom.ObjBoundaries[F].objTarget))
	//					{

	//						//Killing Target
	//						objRoom.ObjBoundaries[F].objTarget.Health = 0;
	//					}
	//				}
	//			}
	//		}
	//		//Checking for gun right 
	//		if (objPlayer.objGunRight.objbulletlist[B].Alive == true)
	//		{
	//			for (int F = 0; F < 100; F++)
	//			{

	//				//Checking Target is alive
	//				if (objRoom.ObjBoundaries[F].objTarget.Health >= 0)
	//				{

	//					//Checking for collision
	//					if (CollisionBox::Intersects(objPlayer.objGunRight.objbulletlist[B], objRoom.ObjBoundaries[F].objTarget))
	//					{

	//						//KillingTarget
	//						objRoom.ObjBoundaries[F].objTarget.Health = 0;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//Bullets VS Targets Corridor Collsion Checks 
	for (int C = 0; C < 6; C++)
	{
		for (int B = 0; B < 50; B++)
		{
			//Checking for Gun Left
			if (objPlayer.objGunLeft.objbulletlist[B].Alive == true)
			{
				for (int F = 0; F < objLevel1Corridor[C].FloorLength; F++)
				{
					
					//Checking Target is alive
					if (objLevel1Corridor[C].objBoundaries[F].objTarget.Health >= 0)
					{
					
					//Checking for colliision	
						if (CollisionBox::Intersects(objPlayer.objGunLeft.objbulletlist[B], objLevel1Corridor[C].objBoundaries[F].objTarget))
						{
							
							//Killing Target
							objLevel1Corridor[C].objBoundaries[F].objTarget.Health = 0;
						}
					}

				}
			}
			
			//Checking for gun right 
			if (objPlayer.objGunRight.objbulletlist[B].Alive == true)
			{
				for (int F = 0; F < objLevel1Corridor[C].FloorLength; F++)
				{
					
					//Checking Target is alive
					if (objLevel1Corridor[C].objBoundaries[F].objTarget.Health >= 0)
					{
						
						//Checking for collision
						if (CollisionBox::Intersects(objPlayer.objGunRight.objbulletlist[B], objLevel1Corridor[C].objBoundaries[F].objTarget))
						{

							//KillingTarget
							objLevel1Corridor[C].objBoundaries[F].objTarget.Health = 0;
						}
					}
				}
			}
		}
	}

	
	
	/*Start Block Collision Check, to stop the player going out of the world*/
	
	//Checking For LeftWall
	if (StartBlock.LeftWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, StartBlock.objLeftWall))
		{

			//Kills the player
			objPlayer.Health = 0;
		}
	}

	//Checking For RightWall
	if (StartBlock.RightWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, StartBlock.objRightWall))
		{

			//Kills the player
			 objPlayer.Health = 0;
		}
	}

	//Checking For FrontWall
	if (StartBlock.FrontWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, StartBlock.objFrontWall))
		{

			//Kills the player
			 objPlayer.Health = 0;
		}
	}

	//Checking For BackWall
	if (StartBlock.BackWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, StartBlock.objBackWall))
		{

			//Kills the player
			 objPlayer.Health = 0;
		}
	}

	//Checking For Roof
	if (StartBlock.Roof == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, StartBlock.objRoof))
		{

			//Kills the player
			 objPlayer.Health = 0;

		}
	}

	//Checking For Floor
	if (StartBlock.Floor == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, StartBlock.objFloor))
		{

			//Kills the player
			objPlayer.Health = 0;
		}
	}

	/*End Block Collision Check, When the player collides with any part of the end block the game ends*/
	
	//Checking For Left Wall
	if (EndBlock.LeftWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, EndBlock.objLeftWall))
		{
			//Goes to end screen
			EndLevel = true;
		}
	}

	//Checking For Right Wall
	if (EndBlock.RightWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, EndBlock.objRightWall))
		{
			//Goes to end screen
			EndLevel = true;
		}
	}

	//Checking For Front Wall
	if (EndBlock.FrontWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, EndBlock.objFrontWall))
		{
			//Goes to end screen
			EndLevel = true;
		}
	}

	//Checking For Back Wall
	if (EndBlock.BackWall == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, EndBlock.objBackWall))
		{
			//Goes to end screen
			EndLevel = true;
		}
	}

	//Checking For Roof
	if (EndBlock.Roof == true)
	{

		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, EndBlock.objRoof))
		{
			//Goes to end screen
			EndLevel = true;

		}
	}

	//Checking For Floor
	if (EndBlock.Floor == true)
	{
		
		//Checking for collison
		if (CollisionBox::Intersects(objPlayer, EndBlock.objFloor))
		{
			//Goes to end screen
			EndLevel = true;
		}
	}



	//Player VS Boundaries Collsion Check for all corridors
	for (int C = 0; C < 6; C++)
	{
		//Goes through each corridor with their floor length, Max floor length is 50
		for (int F = 0; F < objLevel1Corridor[C].FloorLength; F++)
		{
			/*Checks are used to make sure the intersect funciton is not being ran on walls that do not exist*/

			//Backwall Check
			if (objLevel1Corridor[C].objBoundaries[F].BackWall == true)
			{

				//Checking for a Collison
				if (CollisionBox::Intersects(objPlayer, objLevel1Corridor[C].objBoundaries[F].objBackWall))
				{

					//Killing the player if their was a collison
					objPlayer.Health = 0;
				}

			}

			//Frontwall Check
			if (objLevel1Corridor[C].objBoundaries[F].FrontWall == true)
			{

				//Checking for a Collison
				if (CollisionBox::Intersects(objPlayer, objLevel1Corridor[C].objBoundaries[F].objFrontWall))
				{

					//Killing the player if their was a collison
					objPlayer.Health = 0;
				}
			}

			//Leftwall check
			if (objLevel1Corridor[C].objBoundaries[F].LeftWall == true)
			{

				//Checking for a Collison
				if (CollisionBox::Intersects(objPlayer, objLevel1Corridor[C].objBoundaries[F].objLeftWall))
				{

					//Killing the player if their was a collison
					objPlayer.Health = 0;
				}



			}

			//Right Wall check
			if (objLevel1Corridor[C].objBoundaries[F].RightWall == true)
			{
				
				//Checking for a Collison
				if (CollisionBox::Intersects(objPlayer, objLevel1Corridor[C].objBoundaries[F].objRightWall))
				{

					//Killing the player if their was a collison
					objPlayer.Health = 0;
				}

			}

			//Roof Check
			if (objLevel1Corridor[C].objBoundaries[F].Roof == true)
			{		
				
				//Checking for a Collison
				if (CollisionBox::Intersects(objPlayer, objLevel1Corridor[C].objBoundaries[F].objRoof))
				{

					//Killing the player if their was a collison
					objPlayer.Health = 0;
				}

			}

			//Floor Check
			if (objLevel1Corridor[C].objBoundaries[F].Floor == true)
			{
				
				//Checking for a Collison
				if (CollisionBox::Intersects(objPlayer, objLevel1Corridor[C].objBoundaries[F].objFloor))
				{
					
					//Killing the player if their was a collison
					objPlayer.Health = 0;
				}

			}



			}

		}
	
	//Update the Player before the camera as the camera uses the players variables 
	objPlayer.Update();
	
	//Set Camera Eye, At and Up
	Camera.Position.x = -objPlayer.ForwardDirection.x;
	Camera.Position.y = -objPlayer.ForwardDirection.y;
	Camera.Position.z = -objPlayer.ForwardDirection.z;
	Camera.Position = Camera.MultiplyVector(Camera.Position, 3);
	Camera.Position.y += 1;
	Camera.Position = Camera.VectorAdd(Camera.Position, objPlayer.Position);
	Eye = XMVectorSet(Camera.Position.x, Camera.Position.y, Camera.Position.z, 0.0f);
	At = XMVectorSet(objPlayer.Position.x, objPlayer.Position.y, objPlayer.Position.z, 0.0f);
	Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);
	cbNeverChanges.mView = XMMatrixTranspose(g_View);

	//Run Corridor Updates
	objLevel1Corridor[0].Update();
	objLevel1Corridor[1].Update();
	objLevel1Corridor[2].Update();
	objLevel1Corridor[3].Update();
	objLevel1Corridor[4].Update();
	objLevel1Corridor[5].Update();
	objRoom.Update();

	//Update Start Block
	StartBlock.Update();
	
	//Update End Block
	EndBlock.Update();
	objPlayer.Draw();
	//If the player is dead restart the level
	if (objPlayer.Health == 0)
	{
		setup = true;
	}
}
/*MAIN RENDER LOOP*/
void Render()
{
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	//Create Stop Watch for delta time and starts it
	Stopwatch FrameTime;
	FrameTime.Start();


//Calculates Targets Killed
	TargetsKilled = TotalTargets - TargetsLeft; 

	//Calculates TargetsLeft
	TargetsLeft = TotalTargets - TargetsKilled;
	//Create ViewPort
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	
	//Reseting States
	//Clear Screen
	DevCon->ClearRenderTargetView(RenderTargetView, Colors::MidnightBlue);
	DevCon->ClearDepthStencilView(depthStencelView, D3D11_CLEAR_STENCIL || D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	//Setting Layout
	DevCon->IASetInputLayout(g_pVertexLayout);

	//Set Primite Topology
	DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Set Raster
	DevCon->RSSetState(rasterizerState);
	
	//Set Stencil
	DevCon->OMSetDepthStencilState(depthStencilState, 0);
	
	//Set Render Target
	DevCon->OMSetRenderTargets(1, &RenderTargetView, depthStencelView);
	
	//Set View Port
	DevCon->RSSetViewports(1, &vp);
	
	//Set Vertex Buffer
	DevCon->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
	
	//Set Index Buffer
	DevCon->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//Set Projection Matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, Width / Height, 0.01f, 10000.0f);
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	DevCon->UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);
	
	//Set Players Delta Time
	objPlayer.DeltaTime = DeltaTime;
	if (EndLevel == false)
	{
		//Runs Level1 Update Function
		Level1();
		//Pluses one per frame
		CurrentFrameRate += 1;
		//Set 
		Timer = Frametimer.ElapsedSeconds();
		//Frame Per Second Calculation, for every 1 second it will log the current frame rate
		if (Timer >= 1)
		{
			FPS = CurrentFrameRate;
			CurrentFrameRate = 0;
			Frametimer.Restart();
			Timer = 0;
		}
		//Combines Frame Rate to text
		wstring TFPS = std::to_wstring(FPS);
		wstring TText = L"Frame Rate = ";

		TText += TFPS;
		const wchar_t *Text = TText.c_str();
		//Combines Frame Time To TExt
		DeltaTime = FrameTime.ElapsedSeconds();
		wstring DET = std::to_wstring(DeltaTime);
		wstring DText = L"Frame Time = ";

		DText += DET;
		const wchar_t *Text2 = DText.c_str();


		//Combines ShotFired To text
		wstring SHFI = std::to_wstring(objPlayer.Shots);
		wstring ShText = L"Shots Fired = ";
		LevelTime = Leveltimer.ElapsedSeconds();
		ShText += SHFI;
		const wchar_t *Text3 = ShText.c_str();

		//Combines LevelTime To text
		wstring Lev = std::to_wstring(LevelTime);
		wstring LText = L"Level Time = ";
		LText += Lev;
		const wchar_t *Text4 = LText.c_str();

		//Combines Total Targets To Text
		wstring TT = std::to_wstring(TotalTargets);
		wstring TTEXT = L"Total Targets = ";
		TTEXT += TT;
		const wchar_t * Text5 = TTEXT.c_str();

		//Combines Targets Killed To Text
		wstring TK = std::to_wstring(TargetsKilled);
		wstring TKEXT = L"Targets Killed = ";
		TKEXT += TK;
		const wchar_t * Text6 = TKEXT.c_str();


		//Combines Targets Left to text
		wstring TL = std::to_wstring(TargetsLeft);
		wstring TLEXT = L"Targets Left = ";
		TLEXT += TL;
		const wchar_t * Text7 = TLEXT.c_str();


		//Calculates Percentge Left
		PercentageKilled = (TargetsLeft / TotalTargets) * 100;
		//Combines Percentege Left to text
		wstring TP = std::to_wstring(PercentageKilled);
		wstring TPEXT = L"Percentage Left = ";
		TPEXT += TP;
		const wchar_t * Text8 = TPEXT.c_str();


		//Text Draw Stage
		spriteBatch = std::make_unique<DirectX::SpriteBatch>(DevCon);
		spriteFont = std::make_unique<DirectX::SpriteFont>(Device, L"Text/comic_sans_ms_16.spritefont"); //Setting Font
		spriteBatch->Begin();
		spriteFont->DrawString(spriteBatch.get(), L"Storvile Space Corridor Shooter -BY UP814853(Kieran Grist)", XMFLOAT2(0, 0), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text, XMFLOAT2(0, 50), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F)); //Drawing Frame Rate
		spriteFont->DrawString(spriteBatch.get(), Text2, XMFLOAT2(0, 100), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F)); //Drawing Frame Time
																																					 //spriteFont->DrawString(spriteBatch.get(), Text2, XMFLOAT2(0, 00), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F)); //Drawing Frame Time
		spriteFont->DrawString(spriteBatch.get(), Text3, XMFLOAT2(1550, 00), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text4, XMFLOAT2(1550, 50), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text5, XMFLOAT2(1550, 100), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text6, XMFLOAT2(1550, 150), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text7, XMFLOAT2(1550, 200), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text8, XMFLOAT2(1550, 250), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), L"Arrow Keys Move ship \n WASD Rotate Ship \n Space Ship UP \n LControl Ship Down \n F Fire Lasers", XMFLOAT2(0, 750), DirectX::Colors::Black, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteBatch->End();
		swapChain->Present(0, 0); //Swaps the chian
	}
	else
	{
		DevCon->ClearRenderTargetView(RenderTargetView, Colors::Black);
		DevCon->ClearDepthStencilView(depthStencelView, D3D11_CLEAR_STENCIL || D3D11_CLEAR_DEPTH, 1.0f, 0);

		//Checking if X is pressed so the level can start again
		if (KeycodeX == true)
		{
			setup = true;
			EndLevel = false;
		}
		Leveltimer.Stop();
	
		//Combines ShotFired To text
		wstring SHFI = std::to_wstring(objPlayer.Shots);
		wstring ShText = L"Shots Fired = ";
		LevelTime = Leveltimer.ElapsedSeconds();
		ShText += SHFI;
		const wchar_t *Text3 = ShText.c_str();

		//Combines LevelTime To text
		wstring Lev = std::to_wstring(LevelTime);
		wstring LText = L"Level Time = ";
		LText += Lev;
		const wchar_t *Text4 = LText.c_str();

		//Combines Total Targets To Text
		wstring TT = std::to_wstring(TotalTargets);
		wstring TTEXT = L"Total Targets = ";
		TTEXT += TT;
		const wchar_t * Text5 = TTEXT.c_str();

		//Combines Targets Killed To Text
		wstring TK = std::to_wstring(TargetsKilled);
		wstring TKEXT = L"Targets Killed = ";
		TKEXT += TK;
		const wchar_t * Text6 = TKEXT.c_str();


		//Combines Targets Left to text
		wstring TL = std::to_wstring(TargetsLeft);
		wstring TLEXT = L"Targets Left = ";
		TLEXT += TL;
		const wchar_t * Text7 = TLEXT.c_str();


		//Calculates Percentge Left
		PercentageKilled = (TargetsLeft / TotalTargets) * 100;
		//Combines Percentege Left to text
		wstring TP = std::to_wstring(PercentageKilled);
		wstring TPEXT = L"Percentage Left = ";
		TPEXT += TP;
		const wchar_t * Text8 = TPEXT.c_str();


		//Text Draw stage
		spriteBatch = std::make_unique<DirectX::SpriteBatch>(DevCon);
		spriteFont = std::make_unique<DirectX::SpriteFont>(Device, L"Text/comic_sans_ms_16.spritefont"); //Setting Font
		spriteBatch->Begin();
		spriteFont->DrawString(spriteBatch.get(), Text3, XMFLOAT2(1550, 00), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text4, XMFLOAT2(1550, 50), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text5, XMFLOAT2(1550, 100), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text6, XMFLOAT2(1550, 150), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text7, XMFLOAT2(1550, 200), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), L"Level Finished Congrtulations \n your score is on the right \n to start a new level press X", XMFLOAT2(500, 200), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteFont->DrawString(spriteBatch.get(), Text8, XMFLOAT2(1550, 250), DirectX::Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0F), XMFLOAT2(1.0f, 1.0F));
		spriteBatch->End();
		swapChain->Present(0, 0); //Swaps the chian
	}
}