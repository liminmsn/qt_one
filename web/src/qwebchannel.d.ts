declare module 'qwebchannel' {
  export type QWebChannelTransport = {
    webChannelTransport: any;
  };

  export class QWebChannel {
    constructor(
      transport: any,
      initCallback: (channel: { objects: any }) => void
    );
    objects: any;
  }
}

// 扩展全局的 window 对象，让 TS 能够识别 window.qt
interface Window {
  qt?: {
    webChannelTransport: any;
  };
}