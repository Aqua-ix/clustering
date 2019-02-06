
;;; package.el
(require 'package)
;; MELPAを追加
(add-to-list 'package-archives '("melpa" . "https://melpa.org/packages/"))
;; MELPA-stableを追加
(add-to-list 'package-archives '("melpa-stable" . "https://stable.melpa.org/packages/"))
;; Marmaladeを追加
(add-to-list 'package-archives  '("marmalade" . "https://marmalade-repo.org/packages/"))
;; Orgを追加
(add-to-list 'package-archives '("org" . "http://orgmode.org/elpa/"))
;; 初期化
(package-initialize)

;; 環境を日本語、UTF-8にする
(set-locale-environment nil)
(set-language-environment "Japanese")
(set-terminal-coding-system 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-buffer-file-coding-system 'utf-8)
(setq buffer-file-coding-system 'utf-8)
(set-default-coding-systems 'utf-8)
(prefer-coding-system 'utf-8)
(set-fontset-font t 'japanese-jisx0208 "IPAexGothic")
(add-to-list 'face-font-rescale-alist '("IPAexGothic" . 1.08))
;;確認用 : ABCDEあいうえお

;; スタートアップメッセージを表示させない
(setq inhibit-startup-message t)

;; バックアップファイルを作成させない
(setq make-backup-files nil)

;; 終了時にオートセーブファイルを削除する
(setq delete-auto-save-files t)

;; タブにスペースを使用する
(setq-default tab-width 4 indent-tabs-mode nil)

;; 改行コードを表示する
(setq eol-mnemonic-dos "(CRLF)")
(setq eol-mnemonic-mac "(CR)")
(setq eol-mnemonic-unix "(LF)")

;; 複数ウィンドウを禁止する
(setq ns-pop-up-frames nil)

;; ウィンドウを透明にする
;; アクティブウィンドウ／非アクティブウィンドウ（alphaの値で透明度を指定）
(add-to-list 'default-frame-alist '(alpha . (1.00 0.85)))

;; メニューバーを消す
;; (menu-bar-mode -1)

;; ツールバーを消す
(tool-bar-mode -1)

;; 列数を表示する
(column-number-mode t)

;; 行数を表示する
(global-linum-mode t)

;; カーソルの点滅をやめる
(blink-cursor-mode 0)

;; カーソル行をハイライトする
(global-hl-line-mode t)

;; 対応する括弧を光らせる
(show-paren-mode 1)

;; ウィンドウ内に収まらないときだけ、カッコ内も光らせる
(setq show-paren-style 'mixed)
(set-face-background 'show-paren-match-face "grey")
(set-face-foreground 'show-paren-match-face "black")


;; スクロールは１行ごとに
(setq scroll-conservatively 1)


;; C-kで行全体を削除する
(setq kill-whole-line t)

;;; dired設定
(require 'dired-x)

;; "yes or no" の選択を "y or n" にする
(fset 'yes-or-no-p 'y-or-n-p)

;; beep音を消す
(defun my-bell-function ()
  (unless (memq this-command
        '(isearch-abort abort-recursive-edit exit-minibuffer
              keyboard-quit mwheel-scroll down up next-line previous-line
              backward-char forward-char))
    (ding)))
(setq ring-bell-function 'my-bell-function)

;; mozcの設定
;;(require 'mozc)
;;(setq default-input-method "japanese-mozc")

;; flycheckの設定
;;(global-flycheck-mode)
;;(add-hook 'c++-mode-hook (lambda () (setq flycheck-gcc-language-standard "c++11")))

;;; package.el
(require 'package)
;; MELPAを追加
(add-to-list 'package-archives '("melpa" . "https://melpa.org/packages/"))
;; MELPA-stableを追加
(add-to-list 'package-archives '("melpa-stable" . "https://stable.melpa.org/packages/"))
;; Marmaladeを追加
(add-to-list 'package-archives  '("marmalade" . "https://marmalade-repo.org/packages/"))
;; Orgを追加
(add-to-list 'package-archives '("org" . "http://orgmode.org/elpa/"))
;; 初期化
(package-initialize)

;; 環境を日本語、UTF-8にする
(set-locale-environment nil)
(set-language-environment "Japanese")
(set-terminal-coding-system 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-buffer-file-coding-system 'utf-8)
(setq buffer-file-coding-system 'utf-8)
(set-default-coding-systems 'utf-8)
(prefer-coding-system 'utf-8)
(set-fontset-font t 'japanese-jisx0208 "IPAPGothic")

;; スタートアップメッセージを表示させない
(setq inhibit-startup-message t)

;; バックアップファイルを作成させない
(setq make-backup-files nil)

;; 終了時にオートセーブファイルを削除する
(setq delete-auto-save-files t)

;; タブにスペースを使用する
(setq-default tab-width 4 indent-tabs-mode nil)

;; 改行コードを表示する
(setq eol-mnemonic-dos "(CRLF)")
(setq eol-mnemonic-mac "(CR)")
(setq eol-mnemonic-unix "(LF)")

;; 複数ウィンドウを禁止する
(setq ns-pop-up-frames nil)

;; ウィンドウを透明にする
;; アクティブウィンドウ／非アクティブウィンドウ（alphaの値で透明度を指定）
(add-to-list 'default-frame-alist '(alpha . (1.00 0.85)))

;; メニューバーを消す
;; (menu-bar-mode -1)

;; ツールバーを消す
(tool-bar-mode -1)

;; 列数を表示する
(column-number-mode t)

;; 行数を表示する
(global-linum-mode t)

;; カーソルの点滅をやめる
(blink-cursor-mode 0)

;; カーソル行をハイライトする
(global-hl-line-mode t)

;; 対応する括弧を光らせる
(show-paren-mode 1)

;; ウィンドウ内に収まらないときだけ、カッコ内も光らせる
(setq show-paren-style 'mixed)
(set-face-background 'show-paren-match-face "grey")
(set-face-foreground 'show-paren-match-face "black")


;; スクロールは１行ごとに
(setq scroll-conservatively 1)


;; C-kで行全体を削除する
(setq kill-whole-line t)

;;; dired設定
(require 'dired-x)

;; "yes or no" の選択を "y or n" にする
(fset 'yes-or-no-p 'y-or-n-p)

;; beep音を消す
(defun my-bell-function ()
  (unless (memq this-command
        '(isearch-abort abort-recursive-edit exit-minibuffer
              keyboard-quit mwheel-scroll down up next-line previous-line
              backward-char forward-char))
    (ding)))
(setq ring-bell-function 'my-bell-function)

;;バッファ全体の句読点と読点をコンマとピリオドに変換
(defun replace-commaperiod-buffer ()
  (interactive "r")
  (save-excursion
    (replace-string "、" "，" nil (point-min) (point-max))
    (replace-string "。" "．" nil (point-min) (point-max))))

;;選択範囲内の全角英数字を半角英数字に変換
(defun hankaku-eisuu-region (start end)
  (interactive "r")
  (while (string-match
          "[０-９Ａ-Ｚａ-ｚ]+"
          (buffer-substring start end))
    (save-excursion
      (japanese-hankaku-region
       (+ start (match-beginning 0))
       (+ start (match-end 0))
       ))))

;;バッファ全体の全角英数字を半角英数字に変換
(defun hankaku-eisuu-buffer ()
  (interactive)
  (hankaku-eisuu-region (point-min) (point-max)))

;;YaTeXモードの時にのみ動作させる用に条件分岐
(defun replace-commaperiod-before-save-if-needed ()
  (when (memq major-mode
              '(yatex-mode))
    (replace-commaperiod-buffer)(hankaku-eisuu-buffer)))

;;保存前フックに追加
(add-hook 'before-save-hook 'replace-commaperiod-before-save-if-needed)
;;読点と句読点をコンマとピリオドに置き換える
(defun replace-dot-comma ()
  "s/。/．/g; s/、/，/g;する"
  (interactive)
  (let ((curpos (point)))
    (goto-char (point-min))
    (while (search-forward "。" nil t) (replace-match "．"))
    
    (goto-char (point-min))
    (while (search-forward "、" nil t) (replace-match "，"))
    (goto-char curpos)
    ))

(add-hook 'tex-mode-hook
          '(lambda ()
             (add-hook 'before-save-hook 'replace-dot-comma nil 'make-it-local)
             ))

;; mozc
;;(require 'mozc)
;;(setq default-input-method "japanese-mozc")

;; flycheck
;;(global-flycheck-mode)
;;(add-hook 'c++-mode-hook (lambda () (setq flycheck-gcc-language-standard "c++11")))
