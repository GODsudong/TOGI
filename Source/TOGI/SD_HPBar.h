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
	// virtual void NativepreConstruct() override; // C++�� ���� ������
	// virtual void NativeDestruct() override; // C++��  ���� �Ҹ���
	// virtual void NativeTick(const FGeometry& MyGeometry, float IndeltaTime) override; // C++�� ���� Tick
	virtual void NativeConstruct() override; // ������ ����Ʈ�� �÷��Ѷ� ȣ��

	UPROPERTY(Meta = (BindWidget))		// ��ũ�θ� �ۼ������ C++ ���� Ŭ������ ������� ����BP�� ����� ���ε� ����
		class UCanvasPanel* HPBarCanvasPanel;
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* HPBar;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* HPText;

public:
	float GetText();
	float GetPercent();
};
