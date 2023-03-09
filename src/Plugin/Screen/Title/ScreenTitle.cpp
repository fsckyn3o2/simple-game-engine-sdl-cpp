#include "ScreenTitle.h"

#include <Core/BeanManager.h>
#include <Core/TableManager.h>
#include <Core/Assets/GraphicAsset.h>
#include <Core/Table/NameTable.h>

void ScreenTitle::init() {
    nameTable = this->beanManager->tableManager()->nameTable(this->config->nameTableId);

}

void ScreenTitle::update() {

}

void ScreenTitle::render() {
}

void ScreenTitle::handleInput() {

}