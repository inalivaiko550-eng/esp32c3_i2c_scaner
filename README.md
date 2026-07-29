# ESP32-C3 / S3 Hardware I2C Scanner (PlatformIO & Arduino)

---

### 📚 Полезные материалы / Useful Links

Если вы столкнулись с проблемой «чёрного экрана» или молчащего Serial-монитора на чипах ESP32-C3/S3, подробный разбор этих «граблей» с примерами и объяснением причин читайте в моих статьях на Яндекс.Дзен:

* 📑 **[Детектив с I2C: Вчера код работал, сегодня — чёрный экран. Как китайские платы и обновления библиотек ломают проекты](https://dzen.ru/a/amll7vMxCkdEcrvS)** — подробный разбор того, почему меняются пины, как устроен синтаксис новых библиотек Adafruit и как правильно инициализировать дисплеи 1.3" на SH1106.
* 📑 **[Почему молчит Serial Monitor на ESP32-C3 и как это починить в PlatformIO](https://dzen.ru/a/amjoxnESxGFY3fPw)** — всё о встроенном USB-CDC, магии флагов компиляции `ARDUINO_USB_CDC_ON_BOOT` и о том, как не пропускать первые логи при старте контроллера.

---


[🇷🇺 Инструкция на русском языке находится ниже](#russian-readme)

---

### 🇬🇧 English Description

A lightweight and reliable hardware I2C scanner sketch optimized for modern **ESP32-C3** and **ESP32-S3** microcontrollers. 

#### ❓ The Problem it Solves
Many popular cheap development boards (like the **ESP32-C3 SuperMini**) have non-standard hardware pin layouts. When the Arduino-ESP32 framework updates, default I2C pins (`SDA` and `SCL`) can target different pins on software level. This budget scanner forces explicit pin mapping and unlocks the internal USB-CDC Serial connection to reveal exactly where your OLED display or sensors are connected.

#### 🚀 Key Features
* **Explicit Pin Definition:** Forces `Wire.begin(SDA, SCL)` instead of relying on unstable framework defaults.
* **USB-CDC Native Support:** Includes pre-configured `build_flags` for PlatformIO to prevent silent/dead Serial monitors on native USB chips.
* **Boot-Up Wait Logic:** Added short connection loop so you won’t miss the very first scan outputs.

#### 🛠 Configuration (`platformio.ini`)
To make Native USB Serial work flawlessly, add these exact lines to your environment block:
```ini
build_flags = 
    -D ARDUINO_USB_MODE=1
    -D ARDUINO_USB_CDC_ON_BOOT=1
```

---

<a name="russian-readme"></a>
### 🇷🇺 Описание на русском

Легкий и надежный аппаратно-ориентированный I2C-сканер, оптимизированный для современных микроконтроллеров **ESP32-C3** и **ESP32-S3**.

#### ❓ Какую проблему решает
Множество популярных китайских плат (например, ультрадешевые **ESP32-C3 SuperMini**) имеют нестандартную разводку дорожек на текстолите. При фоновом обновлении фреймворка Arduino-ESP32 дефолтные пины `SDA` и `SCL` могут программно поменяться местами, из-за чего дисплеи (SH1106, SSD1306) и датчики внезапно «слепнут». 

Этот сканер принудительно назначает пины и правильно активирует встроенный USB-CDC Serial порт, чтобы показать реальное положение дел на шине.

#### 🚀 Особенности
* **Явное переназначение пинов:** Запускает `Wire.begin(SDA, SCL)` вручную, защищая проект от обновлений ядра плат.
* **Аппаратная поддержка USB-CDC:** Включает корректную инициализацию виртуального COM-порта для чипов без внешней микросхемы-моста (CH340/CP2102).
* **Защита от пропуска логов:** Логика ожидания подключения монитора порта не даст пропустить самый первый цикл сканирования.

#### 🛠 Настройка окружения (`platformio.ini`)
Чтобы Serial-монитор в VS Code не молчал, обязательно добавьте эти флаги компилятора в настройки вашей платы:
```ini
[env:esp32-c3-devkitm-1]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200

# Флаги активации встроенного USB-Serial порта:
build_flags = 
    -D ARDUINO_USB_MODE=1
    -D ARDUINO_USB_CDC_ON_BOOT=1
```

#### 💻 Пример использования (Usage Example)
1. Подключите ваше I2C устройство к пинам (например, `GPIO8` и `GPIO9`).
2. Скопируйте код сканера в `src/main.cpp`.
3. Скомпилируйте и прошейте плату.
4. Откройте **PlatformIO Serial Monitor**. Каждые 3 секунды сканер будет выводить актуальный HEX-адрес обнаруженного устройства (например, `0x3C` или `0x3D`).

---

## 📄 License
This project is open-source and available under the **MIT License**. Feel free to use it in your own diagnostic tools!
