// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SD_HPBar.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API USD_HPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "PlayerReference")
	class AMyPlayer* PlayerReference;
	
protected:
	// virtual void NativeOnInitialized() override;
	// virtual void NativepreConstruct() override; // C++의 위젯 생성자
	// virtual void NativeDestruct() override; // C++의  위젯 소멸자
	// virtual void NativeTick(const FGeometry& MyGeometry, float IndeltaTime) override; // C++의 위젯 Tick
	virtual void NativeConstruct() override; // 생성자 뷰포트에 올려둘때 호출

	UPROPERTY(Meta = (BindWidget))		// 매크로를 작성해줘야 C++ 위젯 클래스를 기반으로 위젯BP를 만들고 바인딩 가능
		class UCanvasPanel* HPBarCanvasPanel;
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* HPBar;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* HPText;

public:
	float GetText();
	float GetPercent();
};
