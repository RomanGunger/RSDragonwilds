import fs from "node:fs/promises";
import { FileBlob, PresentationFile } from "@oai/artifact-tool";

const tmp = "C:/Users/Roman/AppData/Local/Temp/codex-presentations/manual-20260723/plan-prezy/tmp";
const out = "C:/Users/Roman/Documents/Unreal Projects/RuneScapeDW/outputs/AdIndex_City_2026.pptx";
const p = await PresentationFile.importPptx(await FileBlob.load(`${tmp}/template-starter.pptx`));

function shape(slide, name) {
  const found = slide.shapes.items.find((item) => item.name === name);
  if (!found) throw new Error(`Shape "${name}" not found on slide ${slide.index + 1}`);
  return found;
}
function set(slide, name, value) {
  shape(slide, name).text = value;
}
function pos(slide, name, position) {
  shape(slide, name).position = position;
}

const [s1, s2, s3, s4, s5] = p.slides.items;

set(s1, "Заголовок 1", "AdIndex Сити 2026\nРекламный Вояджер");
shape(s1, "Текст 4").delete();
shape(s1, "Текст 5").delete();
s1.speakerNotes.text = "26 июня 2026 года, Москва. Источник: AdIndex, https://adindex.ru/news/marketing/2026/07/1/346747.phtml";

set(s2, "Title 1", "Основные тематические направления");
set(s2, "TextBox 8",
  "НОВАЯ РЕКЛАМНАЯ НОРМАЛЬНОСТЬ\nкто и как формирует правила рынка\n\nИНДУСТРИЯ ВПЕЧАТЛЕНИЙ И КОММУНИКАЦИЙ\nPR, SMM, контент и инфлюенс-маркетинг");
set(s2, "TextBox 10",
  "РЕКЛАМНЫЙ ИНВЕНТАРЬ И ТЕХНОЛОГИИ · AdTech и размещение\nТЕХНОЛОГИИ И АНАЛИТИКА · эконометрика, SEO, сквозная аналитика");
set(s2, "TextBox 5",
  "ЭКОСИСТЕМА В ЦИФРЕ И ЦИФРАХ · digital, видео и DOOH\nРЕКЛАМНЫЕ КЕЙСЫ · практические разборы");
set(s2, "TextBox 11",
  "ЭФФЕКТИВНАЯ РЕКЛАМА · рост продаж и отдачи\nПОВЕДЕНЧЕСКАЯ ЭКОНОМИКА · от истории до транзакции");
pos(s2, "TextBox 10", { left: 128.47, top: 288.49, width: 1187.29, height: 108 });
pos(s2, "TextBox 5", { left: 130.53, top: 405, width: 1187.29, height: 130 });
s2.speakerNotes.text = "Восемь тематических потоков. Источники: пользовательский план и официальная программа AdIndex City 2026.";

set(s3, "Title 1", "Ключевые сигналы от спикеров");
set(s3, "TextBox 8",
  "ЯКОВ ПЕЙСАХЗОН · «Авито Реклама»\nБрендам важно видеть не только интересы, но и жизненные события — переезд, питомца, продажу автомобиля.");
set(s3, "TextBox 10",
  "АЛЕКСЕЙ БАХТЕРОВ · Media Instinct Group\nИндустрия переходит от эпохи программного обеспечения к эпохе ИИ — значительно более быстрой.");
set(s3, "TextBox 5",
  "ТАТЬЯНА КОВАЛЕВСКАЯ · T2 AdTech\nТрадиционные медиа уступают персонализированным алгоритмическим лентам.");
set(s3, "TextBox 11",
  "ОЛЕГ ТЕМБОТОВ · Mediasystem\nДолгосрочные модели уступают тактической гибкости — без отказа от последовательного брендбилдинга.");
pos(s3, "TextBox 10", { left: 128.47, top: 286, width: 1187.29, height: 105 });
pos(s3, "TextBox 5", { left: 130.53, top: 395, width: 1187.29, height: 125 });
s3.speakerNotes.text = "Источник формулировок: https://adindex.ru/news/marketing/2026/07/1/346747.phtml";

set(s4, "Заголовок 1", "Главные темы ТВ-рекламы");
set(s4, "Текст 2",
  "ГЛАВНАЯ МЫСЛЬ\nРекламодатель покупает не ТВ-инвентарь, а видеоконтакт с человеком — в эфире, Smart TV, онлайн-кинотеатре или мобильном видео.\n\nКЛЮЧЕВЫЕ ВЫВОДЫ\n• Классическое ТВ остается фундаментом кампании.\n• Цифровой контент всё чаще смотрят на телевизоре.\n• Кампании сразу планируются под несколько типов видеопотребления.\n• ТВ-экран становится точкой входа в цифровую рекламу.\n• Рынок движется к омниканальному видеопланированию.\n• Решения всё чаще принимаются на основе больших данных и ИИ.");
s4.speakerNotes.text = "Сводка по пользовательскому плану.";

set(s5, "Title 1", "Что это значит для ТВ-рынка");
set(s5, "TextBox 8",
  "ЛИНЕЙНОЕ ТВ СОХРАНЯЕТ ЗНАЧЕНИЕ\nОно остается массовым фундаментом видеокампаний.");
set(s5, "TextBox 10",
  "DIGITAL TV И CTV — ОБЯЗАТЕЛЬНАЯ ЧАСТЬ ВИДЕОМИКСА\nОнлайн-видео и телевизионный экран постепенно объединяются.");
set(s5, "TextBox 5",
  "ДАННЫЕ И ИСКУССТВЕННЫЙ ИНТЕЛЛЕКТ\nстановятся основой медиапланирования и выбора контакта.");
set(s5, "TextBox 11",
  "ГЛАВНАЯ ЗАДАЧА РЫНКА — НЕ РАЗДЕЛЯТЬ ТВ И DIGITAL");
s5.speakerNotes.text = "Итоговая управленческая рамка по пользовательскому плану.";

await fs.mkdir(`${tmp}/preview/final`, { recursive: true });
await fs.mkdir(`${tmp}/layout/final`, { recursive: true });
for (const [i, slide] of p.slides.items.entries()) {
  const n = String(i + 1).padStart(2, "0");
  const png = await p.export({ slide, format: "png", scale: 1 });
  await fs.writeFile(`${tmp}/preview/final/slide-${n}.png`, new Uint8Array(await png.arrayBuffer()));
  const layout = await slide.export({ format: "layout" });
  await fs.writeFile(`${tmp}/layout/final/slide-${n}.layout.json`, await layout.text(), "utf8");
}
const montage = await p.export({ format: "webp", montage: true, scale: 1 });
await fs.writeFile(`${tmp}/preview/final/montage.webp`, new Uint8Array(await montage.arrayBuffer()));
await fs.mkdir("C:/Users/Roman/Documents/Unreal Projects/RuneScapeDW/outputs", { recursive: true });
const pptx = await PresentationFile.exportPptx(p);
await pptx.save(out);
console.log(out);
