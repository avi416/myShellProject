MyShell Project
MyShell הוא מימוש בסיסי של Shell (סביבת פקודות) בשפת C, כחלק ממטלת הגשה בקורס מערכות הפעלה. הפרויקט כולל פקודות פנימיות (Built-In) והרחבה לפקודות חיצוניות באמצעות System Calls.

🚀 תכונות עיקריות
📌 פקודות פנימיות (Built-In)
פקודה	תיאור
cd <path>	מעבר לתיקייה (נתיב) חדשה.
echo "some text"	הדפסת טקסט למסך.
echo "some text" > file.txt	כתיבת טקסט לקובץ (מוחק תוכן קיים).
echo "some text" >> file.txt	הוספת טקסט לקובץ (Append).
cp <src> <dest>	העתקת קובץ.
move <src> <dest>	העברת קובץ או שינוי שמו.
delete <file>	מחיקת קובץ.
dir	הצגת תוכן התיקייה הנוכחית (דמוי ls).
read <file>	קריאת תוכן קובץ והדפסתו למסך (דמוי cat).
wordCount <option> <file>	ספירת שורות / מילים / תווים בקובץ (דמוי wc).
אפשרויות לפקודה wordCount:

-l : ספירת שורות.
-w : ספירת מילים.
-c : ספירת תווים.
📌 פקודות חיצוניות
כל פקודה שאינה פנימית תבוצע דרך פונקציית systemCall, שמבצעת execvp. לדוגמה:

ls -l
cat file.txt
grep "text" file.txt
📌 צינור (Pipe)
שימוש בסימן | בין שתי פקודות, לדוגמה:

ls -l | grep .c
יגרום להרצת שתי פקודות במקביל, כך שהפלט של הראשונה (ls -l) עובר ישירות כקלט לשנייה (grep .c).

📌 פקודת exit
סיום ריצת ה-Shell והיציאה מהתוכנית.

🏗️ מבנה הפרויקט
קובץ	תיאור
myShell.c	מכיל את הפונקציה main(), בה מתבצעת הלולאה הראשית של ה-Shell.
myShell.h	קובץ הכותרת עבור myShell.c.
myFunctionsShell.c	מממש את כל הפונקציות הפנימיות (cd, echo, cp, וכו').
myFunctionsShell.h	הצהרות לפונקציות הפנימיות.
makefile	קובץ קומפילציה (אופציונלי) לניהול Build ו-Clean.
⚙️ הוראות הידור והרצה
📌 הידור (קומפילציה) עם makefile
make
הפקודה תיצור קובץ הרצה בשם myShell.

📌 הרצה
./myShell
לאחר מכן תראה את ההודעה הראשונית (Welcome) ואת ה-Prompt של ה-Shell.

📌 ניקוי קבצי .o
make clean
מנקה את קבצי ההידור הישנים.

🛠️ שימוש ופקודות לדוגמה
cd Documents                  # מעבר לתיקיית Documents

echo "Hello World" > file.txt  # יצירת קובץ וכתיבת טקסט

echo "Another line" >> file.txt # הוספת שורה לקובץ

read file.txt                 # קריאת תוכן קובץ

wordCount -l file.txt         # ספירת שורות בקובץ

ls -l | grep .c               # שימוש בצינור (Pipe) בין פקודות

exit                          # יציאה מה-Shell
⚠️ הערות
בשמות קבצים המכילים רווחים, יש להשתמש במרכאות:
cp "my source file.txt" "my destination file.txt"
הפקודות פועלות בסביבת Linux / WSL. ב-Windows טהור ייתכן ויידרשו התאמות נוספות.
הפקודה rename() (בפקודת move) לא תמיד תעבוד על העברת קבצים בין מחיצות שונות. במקרה כזה עדיף לבצע cp ואז delete.
🎯 תרומה ושיפורים
ניתן להרחיב את ה-Shell לפקודות נוספות, להוסיף תמיכה במשתני סביבה וכו'. נשמח לקבל Pull Request או הערות לשיפור!
