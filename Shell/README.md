
MyShell Project
פרויקט MyShell הוא מימוש בסיסי של Shell (סביבת פקודות) בשפת C, כחלק ממטלת הגשה בקורס מערכות הפעלה. הפרויקט כולל פקודות פנימיות (Built-In) והרחבה לפקודות חיצוניות באמצעות קריאות מערכת (System Calls).

תכונות עיקריות
פקודות פנימיות (Built-In):

cd <path>: מעבר לתיקייה (נתיב) חדשה.
echo "some text": הדפסת טקסט למסך.
echo "some text" > file.txt: כתיבת טקסט לקובץ (מוחק תוכן קיים).
echo "some text" >> file.txt: הוספת טקסט לקובץ (Append).
cp <source> <destination>: העתקת קובץ.
move <source> <destination>: העברת קובץ או שינוי שמו.
delete <file>: מחיקת קובץ.
dir: הצגת תוכן התיקייה הנוכחית (דמוי ls).
read <file>: קריאת תוכן קובץ והדפסתו למסך (דמוי cat).
wordCount <option> <file>: ספירת שורות / מילים / תווים בקובץ (דמוי wc):
-l: ספירת שורות
-w: ספירת מילים
-c: ספירת תווים
פקודות חיצוניות:

כל פקודה שאינה פנימית תעבור לפונקציה systemCall, שמבצעת execvp על הפקודה.
לדוגמה: ls -l, grep text, cat file, וכו’.
צינור (Pipe):

שימוש בסימן | בין שתי פקודות, לדוגמה:
bash
Copy
Edit
ls -l | grep .c
יגרום להרצת שתי פקודות במקביל, כך שהפלט של הראשונה (ls -l) עובר ישירות כקלט לשנייה (grep .c).
פקודת exit:

סיום ריצת ה־Shell והיציאה מהתוכנית.
מבנה הפרויקט
הפרויקט מכיל קבצים עיקריים:

myShell.c
מכיל את פונקציית main(), בה מתבצעת הלולאה הראשית של ה־Shell. כאן נקראים לפונקציות המימוש (cd, echo, וכד’) בהתאם לפקודה שהתקבלה מהמשתמש.

myShell.h
קובץ הכותרת עבור myShell.c (מכיל הצהרות/הגדרות כלליות אם נדרש).

myFunctionsShell.c
מממש את כל הפונקציות הפנימיות (cd, echo, cp, move, וכו’), וכן פונקציות עזר כמו splitArguments().

myFunctionsShell.h
הצהרות לפונקציות הפנימיות ותלויות בהן.

makefile (אופציונלי)
מגדיר את תהליך הקומפילציה והלינקינג, כמו גם מטרות make clean, make run וכו’.

הוראות הידור והרצה
הידור (קומפילציה) עם makefile

bash
Copy
Edit
make
הפקודה תיצור קובץ הרצה בשם myShell (בהתאם להגדרות ה־makefile).

הרצה

bash
Copy
Edit
./myShell
תראה את ההודעה הראשונית (Welcome) ולאחר מכן prompt צבעוני (משתמש@מחשב:נתיב$).

ניקוי קבצי .o

bash
Copy
Edit
make clean
מנקה את קבצי ההידור הישנים.

שימוש ופקודות לדוגמה
bash
Copy
Edit
cd Documents
מעבר לתיקיית Documents (חייבת להיות קיימת).

bash
Copy
Edit
echo "Hello World" > file.txt
יוצר/מחליף תוכן הקובץ file.txt בטקסט "Hello World".

bash
Copy
Edit
echo "Another line" >> file.txt
מוסיף שורה נוספת ל־file.txt.

bash
Copy
Edit
read file.txt
מציג את תוכן הקובץ file.txt.

bash
Copy
Edit
wordCount -l file.txt
מציג כמה שורות יש בקובץ file.txt.

bash
Copy
Edit
ls -l | grep .c
פקודה חיצונית שמשתמשת בצינור (Pipe) בין ls -l ל־grep .c.

bash
Copy
Edit
exit
יציאה מה־Shell.

הערות וידועות
בשמות קבצים המכילים רווחים, יש להשתמש במרכאות, לדוגמה:
bash
Copy
Edit
cp "my source file.txt" "my destination file.txt"
הפקודות פועלות ברובן בסביבת לינוקס/WSL. ייתכן שב־Windows טהור יידרשו התאמות נוספות.
rename() (בשימוש move) לא תמיד יעבוד על העברת קבצים בין מחיצות שונות. במקרה כזה תידרש העתקה (cp) ואז מחיקה.
תרומה ושיפורים
ניתן להרחיב את ה־Shell לפקודות פנימיות נוספות, לטפל בהרשאות (permissions), להוסיף תמיכה במשתני סביבה וכו’.
מוזמנים לשלוח Pull Request או לפנות בשאלות/הערות.
רישיון
ניתן להשתמש בקוד לצרכי למידה ותרגול. אין אחריות על נזקים וכו’.