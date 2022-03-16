#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:

public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

public:
    MainGame() {}
    ~MainGame() {}
};
/*
스키마란?
-데이터베이스 내에 어떤 구조로 데이터가 저장되는가를 나타내는 데이터베이스 구조
ㄴ 개체의 특성 : 속성
ㄴ 속성들의 집합 : 독립된 개체
ㄴ 개체들 사이에 존재하는 '관계'

스키마의 종류
스키마는 내부,외부,개념 스키마가 있다.

*/
/*
과제
캐릭터 상태 정의
-캐릭터에 대한 모든것
ㄴ 이미지, 현재 상태, 체력,이 캐릭터 제이슨파일에 있어야함
ㄴ 캐릭터 오른쪽으로 이미지 바뀌고 하는것도 같이 읽어올수있게끔...


*/