# Inventory System - Dawn of Ages

## Dateien
- `InventoryComponent.h` - Header
- `InventoryComponent.cpp` - Implementation

## Installation in UE 5.7

1. Erstelle ein C++ Third Person Projekt in UE 5.7

2. Öffne den Source-Ordner:
   ```
   DeinProjekt/Source/DeinProjekt/
   ```

3. Kopiere die Dateien dort hin

4. In UE: Rechtsklick auf .uproject → "Generate Visual Studio project files"

5. Kompilieren (F7 in Visual Studio)

6. Blueprint erstellen:
   - Rechtsklick im Content Browser → "Blueprint Class"
   - Suchen nach "InventoryComponent"
   - An Spieler-Character anhängen

## Funktionen
- `AddItem` - Item hinzufügen (Name, Icon, Menge)
- `RemoveItem` - Item entfernen
- `UseItem` - Item benutzen
- `GetItemAt` - Item von Slot lesen
- 20 Slots, Max 99 pro Stack